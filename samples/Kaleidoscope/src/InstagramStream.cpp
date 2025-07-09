//
//	InstagramStream.cpp
//	InstaScope
//
//	Created by Greg Kepler on 6/9/12.
//	Copyright (c) 2012 The Barbarian Group. All rights reserved.
//

#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/Thread.h"
#include "cinder/Function.h"
#include "cinder/Json.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"
#include "cinder/Log.h"
#include "cinder/Utilities.h"
#include "cinder/Url.h"
#include "cinder/Base64.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>

#include "InstagramStream.h"

static const int BUFFER_SIZE = 10;

using namespace std;
using namespace ci;
using namespace ci::app;

// Instagram Basic Display API v2 endpoints
static const string INSTAGRAM_API_URL = "https://graph.instagram.com/v12.0";
static const string INSTAGRAM_AUTH_URL = "https://api.instagram.com/oauth/authorize";
static const string INSTAGRAM_TOKEN_URL = "https://api.instagram.com/oauth/access_token";

// Demo images for when API is not available
static const vector<string> DEMO_IMAGES = {
    "https://picsum.photos/600/600?random=1",
    "https://picsum.photos/600/600?random=2", 
    "https://picsum.photos/600/600?random=3",
    "https://picsum.photos/600/600?random=4",
    "https://picsum.photos/600/600?random=5",
    "https://picsum.photos/600/600?random=6",
    "https://picsum.photos/600/600?random=7",
    "https://picsum.photos/600/600?random=8",
    "https://picsum.photos/600/600?random=9",
    "https://picsum.photos/600/600?random=10"
};

static const vector<string> DEMO_USERS = {
    "demo_user_1", "demo_user_2", "demo_user_3", "demo_user_4", "demo_user_5",
    "demo_user_6", "demo_user_7", "demo_user_8", "demo_user_9", "demo_user_10"
};

nlohmann::json queryInstagram(const std::string &searchUrl)
{
    Url url(searchUrl, true);
    auto data = loadUrl(url);
    std::stringstream buffer;
    buffer << data->getBuffer()->getData();
    return nlohmann::json::parse(buffer.str());
}

// OAuth Authentication Methods
std::string InstagramStream::getAuthUrl(const std::string& clientId, const std::string& redirectUri)
{
    std::string authUrl = INSTAGRAM_AUTH_URL + "?client_id=" + clientId +
                          "&redirect_uri=" + Url::encode(redirectUri) +
                          "&scope=user_profile,user_media" +
                          "&response_type=code";
    return authUrl;
}

std::string InstagramStream::exchangeCodeForToken(const std::string& clientId, const std::string& clientSecret, 
                                                 const std::string& code, const std::string& redirectUri)
{
    try {
        // Prepare POST data
        std::string postData = "client_id=" + clientId +
                              "&client_secret=" + clientSecret +
                              "&grant_type=authorization_code" +
                              "&redirect_uri=" + Url::encode(redirectUri) +
                              "&code=" + code;
        
        // Create URL request
        Url url(INSTAGRAM_TOKEN_URL, true);
        url.setPostData(postData);
        
        auto response = loadUrl(url);
        std::stringstream buffer;
        buffer << response->getBuffer()->getData();
        
        auto jsonResponse = nlohmann::json::parse(buffer.str());
        
        if (jsonResponse.contains("access_token")) {
            std::string accessToken = jsonResponse["access_token"].get<std::string>();
            std::string refreshToken = "";
            if (jsonResponse.contains("refresh_token")) {
                refreshToken = jsonResponse["refresh_token"].get<std::string>();
            }
            
            // Save tokens
            saveAccessToken(accessToken, refreshToken);
            return accessToken;
        } else {
            CI_LOG_E("Failed to exchange code for token: " << buffer.str());
            return "";
        }
    }
    catch (const std::exception& e) {
        CI_LOG_E("Exception in exchangeCodeForToken: " << e.what());
        return "";
    }
}

std::string InstagramStream::refreshAccessToken(const std::string& clientId, const std::string& clientSecret, 
                                              const std::string& refreshToken)
{
    try {
        // Prepare POST data
        std::string postData = "client_id=" + clientId +
                              "&client_secret=" + clientSecret +
                              "&grant_type=refresh_token" +
                              "&refresh_token=" + refreshToken;
        
        // Create URL request
        Url url(INSTAGRAM_TOKEN_URL, true);
        url.setPostData(postData);
        
        auto response = loadUrl(url);
        std::stringstream buffer;
        buffer << response->getBuffer()->getData();
        
        auto jsonResponse = nlohmann::json::parse(buffer.str());
        
        if (jsonResponse.contains("access_token")) {
            std::string accessToken = jsonResponse["access_token"].get<std::string>();
            std::string newRefreshToken = refreshToken;
            if (jsonResponse.contains("refresh_token")) {
                newRefreshToken = jsonResponse["refresh_token"].get<std::string>();
            }
            
            // Save tokens
            saveAccessToken(accessToken, newRefreshToken);
            return accessToken;
        } else {
            CI_LOG_E("Failed to refresh token: " << buffer.str());
            return "";
        }
    }
    catch (const std::exception& e) {
        CI_LOG_E("Exception in refreshAccessToken: " << e.what());
        return "";
    }
}

bool InstagramStream::saveAccessToken(const std::string& accessToken, const std::string& refreshToken)
{
    try {
        std::ofstream tokenFile("instagram_tokens.txt");
        if (tokenFile.is_open()) {
            tokenFile << "access_token=" << accessToken << std::endl;
            if (!refreshToken.empty()) {
                tokenFile << "refresh_token=" << refreshToken << std::endl;
            }
            tokenFile.close();
            return true;
        }
    }
    catch (const std::exception& e) {
        CI_LOG_E("Exception saving tokens: " << e.what());
    }
    return false;
}

std::string InstagramStream::loadAccessToken()
{
    try {
        std::ifstream tokenFile("instagram_tokens.txt");
        if (tokenFile.is_open()) {
            std::string line;
            while (std::getline(tokenFile, line)) {
                if (line.find("access_token=") == 0) {
                    return line.substr(13); // Remove "access_token=" prefix
                }
            }
            tokenFile.close();
        }
    }
    catch (const std::exception& e) {
        CI_LOG_E("Exception loading access token: " << e.what());
    }
    return "";
}

std::string InstagramStream::loadRefreshToken()
{
    try {
        std::ifstream tokenFile("instagram_tokens.txt");
        if (tokenFile.is_open()) {
            std::string line;
            while (std::getline(tokenFile, line)) {
                if (line.find("refresh_token=") == 0) {
                    return line.substr(14); // Remove "refresh_token=" prefix
                }
            }
            tokenFile.close();
        }
    }
    catch (const std::exception& e) {
        CI_LOG_E("Exception loading refresh token: " << e.what());
    }
    return "";
}

void InstagramStream::clearStoredTokens()
{
    try {
        std::remove("instagram_tokens.txt");
    }
    catch (const std::exception& e) {
        CI_LOG_E("Exception clearing tokens: " << e.what());
    }
}

InstagramStream::InstagramStream(const string &clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mSearchPhrase( "" ),
mThread( nullptr ),
mIsConnected( false ),
mClientId( clientId ),
mDemoMode( clientId.empty() || clientId == "demo" )
{
    // Try to load stored access token first
    std::string accessToken = loadAccessToken();
    if (!accessToken.empty()) {
        mClientId = accessToken;
        mDemoMode = false;
        console() << "Using stored Instagram access token" << std::endl;
    }
    
    if (mDemoMode) {
        startDemoThread();
    } else {
        // Note: Instagram Basic Display API requires user authentication
        // This is a simplified implementation - in production you'd need proper OAuth flow
        startThread(INSTAGRAM_API_URL + "/me/media?fields=id,media_type,media_url,thumbnail_url,username&access_token=" + mClientId);
    }
}

InstagramStream::InstagramStream( const std::string &searchPhrase, const string &clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mSearchPhrase( searchPhrase ),
mThread( nullptr ),
mIsConnected( false ),
mClientId( clientId ),
mDemoMode( clientId.empty() || clientId == "demo" )
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        // For tag search, we'd need to use the Instagram Graph API which requires business accounts
        // For now, fall back to demo mode
        startDemoThread();
    }
}

InstagramStream::InstagramStream( const std::string &searchPhrase, const int &minId, const int &maxId, const std::string &clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mSearchPhrase( searchPhrase ),
mThread( nullptr ),
mIsConnected( false ),
mClientId( clientId ),
mDemoMode( clientId.empty() || clientId == "demo" )
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        startDemoThread(); // Fall back to demo mode for now
    }
}

InstagramStream::InstagramStream(ci::vec2 loc, float dist, int minTs, int maxTs, std::string clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mSearchPhrase( "" ),
mThread( nullptr ),
mIsConnected( false ),
mClientId( clientId ),
mDemoMode( clientId.empty() || clientId == "demo" )
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        startDemoThread(); // Location search requires different API endpoints
    }
}

InstagramStream::InstagramStream(ci::vec2 loc, float dist, std::string clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mSearchPhrase( "" ),
mThread( nullptr ),
mIsConnected( false ),
mClientId( clientId ),
mDemoMode( clientId.empty() || clientId == "demo" )
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        startDemoThread(); // Location search requires different API endpoints
    }
}

InstagramStream::InstagramStream(ci::vec2 loc, std::string clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mSearchPhrase( "" ),
mThread( nullptr ),
mIsConnected( false ),
mClientId( clientId ),
mDemoMode( clientId.empty() || clientId == "demo" )
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        startDemoThread(); // Location search requires different API endpoints
    }
}

void InstagramStream::startThread(string url){
	mThread = std::make_shared<std::thread>( bind( &InstagramStream::serviceGrams, this, url ) );
}

void InstagramStream::startDemoThread() {
    mThread = std::make_shared<std::thread>( bind( &InstagramStream::serviceDemoGrams, this ) );
}

InstagramStream::~InstagramStream()
{
	mCanceled = true;
	mBuffer.cancel();
	mThread->join();
}

// Function the background thread lives in for real Instagram API
void InstagramStream::serviceGrams(std::string url)
{
    ThreadSetup threadSetup;
    std::string nextQueryString = url;

    nlohmann::json searchResults;
    nlohmann::json::iterator resultIt = searchResults.end();
    nlohmann::json queryResult;
    while (!mCanceled) {
        if (resultIt == searchResults.end()) {
            try {
                queryResult = queryInstagram(nextQueryString);
                // the next query will be the "next_url" of this one.
                if (queryResult.contains("pagination") && queryResult["pagination"].contains("next_url"))
                    nextQueryString = queryResult["pagination"]["next_url"].get<std::string>();
                searchResults = queryResult["data"];
                resultIt = searchResults.begin();
                mIsConnected = true;
            }
            catch (const std::exception &exc) {
                CI_LOG_W("Instagram API exception caught: " << exc.what());
                // Optionally log queryResult and nextQueryString
                if (queryResult.contains("error") && queryResult["error"].contains("code")) {
                    console() << "Instagram API error: " << queryResult["error"]["code"].get<std::string>() << std::endl;
                    mIsConnected = false;
                }
                ci::sleep(1000); // try again in 1 second
            }
        }
        if (resultIt != searchResults.end()) {
            try {
                std::string userName = (*resultIt)["username"].get<std::string>();
                std::string imageUrl = (*resultIt)["media_url"].get<std::string>();
                Surface image(loadImage(loadUrl(imageUrl)));
                mBuffer.pushFront(Instagram(userName, imageUrl, image));
            }
            catch (const std::exception &exc) {
                CI_LOG_W("Instagram data processing exception: " << exc.what());
            }
            ++resultIt;
        }
    }
}

// Function for demo mode - generates random images from Lorem Picsum
void InstagramStream::serviceDemoGrams()
{
    ThreadSetup threadSetup;
    int demoIndex = 0;
    
    while (!mCanceled) {
        try {
            // Cycle through demo images
            std::string imageUrl = DEMO_IMAGES[demoIndex % DEMO_IMAGES.size()];
            std::string userName = DEMO_USERS[demoIndex % DEMO_USERS.size()];
            
            Surface image(loadImage(loadUrl(imageUrl)));
            mBuffer.pushFront(Instagram(userName, imageUrl, image));
            
            demoIndex++;
            mIsConnected = true;
            
            // Wait a bit before loading the next image
            ci::sleep(2000);
        }
        catch (const std::exception &exc) {
            CI_LOG_W("Demo mode exception: " << exc.what());
            ci::sleep(1000);
        }
    }
}

bool InstagramStream::hasInstagramAvailable()
{
	return mBuffer.isNotEmpty();
}

Instagram InstagramStream::getNextInstagram()
{
	Instagram result;
    mBuffer.popBack( &result );
	return result;
}

bool InstagramStream::isConnected()
{
	return mIsConnected;
}

bool InstagramStream::isDemoMode()
{
    return mDemoMode;
}