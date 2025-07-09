#include "InstagramStream.h"
#include "InstagramOAuth.h"
#include "cinder/app/App.h"
#include "cinder/Rand.h"
#include "cinder/Thread.h"
#include "cinder/Function.h"
#include "cinder/Json.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"
#include "cinder/Log.h"
#include "cinder/Utilities.h"
#include <nlohmann/json.hpp>

using namespace ci;
using namespace ci::app;

static const int BUFFER_SIZE = 10;

// Instagram Basic Display API v2 endpoints
static const string INSTAGRAM_API_URL = "https://graph.instagram.com/v12.0";

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

nlohmann::json queryInstagram(const std::string& searchUrl)
{
    Url url(searchUrl, true);
    auto data = loadUrl(url);
    std::stringstream buffer;
    buffer << data->getBuffer()->getData();
    return nlohmann::json::parse(buffer.str());
}

InstagramStream::InstagramStream(const string& clientId)
: mBuffer(BUFFER_SIZE), // our buffer of instagrams can hold up to 10
mCanceled(false),
mSearchPhrase(""),
mThread(nullptr),
mIsConnected(false),
mClientId(clientId),
mDemoMode(clientId.empty() || clientId == "demo")
{
    // Try to load stored access token first
    std::string accessToken = InstagramOAuth::loadAccessToken();
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

InstagramStream::InstagramStream(const std::string& searchPhrase, const string& clientId)
: mBuffer(BUFFER_SIZE), // our buffer of instagrams can hold up to 10
mCanceled(false),
mSearchPhrase(searchPhrase),
mThread(nullptr),
mIsConnected(false),
mClientId(clientId),
mDemoMode(clientId.empty() || clientId == "demo")
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        // For tag search, we'd need to use the Instagram Graph API which requires business accounts
        // For now, fall back to demo mode
        startDemoThread();
    }
}

InstagramStream::InstagramStream(const std::string& searchPhrase, const int& minId, const int& maxId, const std::string& clientId)
: mBuffer(BUFFER_SIZE), // our buffer of instagrams can hold up to 10
mCanceled(false),
mSearchPhrase(searchPhrase),
mThread(nullptr),
mIsConnected(false),
mClientId(clientId),
mDemoMode(clientId.empty() || clientId == "demo")
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        startDemoThread(); // Fall back to demo mode for now
    }
}

InstagramStream::InstagramStream(vec2 loc, float dist, int minTs, int maxTs, std::string clientId)
: mBuffer(BUFFER_SIZE), // our buffer of instagrams can hold up to 10
mCanceled(false),
mSearchPhrase(""),
mThread(nullptr),
mIsConnected(false),
mClientId(clientId),
mDemoMode(clientId.empty() || clientId == "demo")
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        startDemoThread(); // Location search requires different API endpoints
    }
}

InstagramStream::InstagramStream(vec2 loc, float dist, std::string clientId)
: mBuffer(BUFFER_SIZE), // our buffer of instagrams can hold up to 10
mCanceled(false),
mSearchPhrase(""),
mThread(nullptr),
mIsConnected(false),
mClientId(clientId),
mDemoMode(clientId.empty() || clientId == "demo")
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        startDemoThread(); // Location search requires different API endpoints
    }
}

InstagramStream::InstagramStream(vec2 loc, std::string clientId)
: mBuffer(BUFFER_SIZE), // our buffer of instagrams can hold up to 10
mCanceled(false),
mSearchPhrase(""),
mThread(nullptr),
mIsConnected(false),
mClientId(clientId),
mDemoMode(clientId.empty() || clientId == "demo")
{
    if (mDemoMode) {
        startDemoThread();
    } else {
        startDemoThread(); // Location search requires different API endpoints
    }
}

void InstagramStream::startThread(string url) {
    mThread = std::make_shared<std::thread>(bind(&InstagramStream::serviceGrams, this, url));
}

void InstagramStream::startDemoThread() {
    mThread = std::make_shared<std::thread>(bind(&InstagramStream::serviceDemoGrams, this));
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
            catch (const std::exception& exc) {
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
            catch (const std::exception& exc) {
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
        catch (const std::exception& exc) {
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
    mBuffer.popBack(&result);
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