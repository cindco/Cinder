#include "InstagramOAuth.h"
#include "cinder/Url.h"
#include "cinder/Utilities.h"
#include "cinder/Log.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>

namespace ci {

// Instagram Basic Display API v2 endpoints
const std::string InstagramOAuth::INSTAGRAM_AUTH_URL = "https://api.instagram.com/oauth/authorize";
const std::string InstagramOAuth::INSTAGRAM_TOKEN_URL = "https://api.instagram.com/oauth/access_token";
const std::string InstagramOAuth::TOKEN_FILE_NAME = "instagram_tokens.txt";

std::string InstagramOAuth::getAuthUrl(const std::string& clientId, const std::string& redirectUri)
{
    std::string authUrl = INSTAGRAM_AUTH_URL + "?client_id=" + clientId +
                          "&redirect_uri=" + Url::encode(redirectUri) +
                          "&scope=user_profile,user_media" +
                          "&response_type=code";
    return authUrl;
}

std::string InstagramOAuth::exchangeCodeForToken(const std::string& clientId, const std::string& clientSecret, 
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

std::string InstagramOAuth::refreshAccessToken(const std::string& clientId, const std::string& clientSecret, 
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

bool InstagramOAuth::saveAccessToken(const std::string& accessToken, const std::string& refreshToken)
{
    try {
        std::ofstream tokenFile(TOKEN_FILE_NAME);
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

std::string InstagramOAuth::loadAccessToken()
{
    try {
        std::ifstream tokenFile(TOKEN_FILE_NAME);
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

std::string InstagramOAuth::loadRefreshToken()
{
    try {
        std::ifstream tokenFile(TOKEN_FILE_NAME);
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

void InstagramOAuth::clearStoredTokens()
{
    try {
        std::remove(TOKEN_FILE_NAME.c_str());
    }
    catch (const std::exception& e) {
        CI_LOG_E("Exception clearing tokens: " << e.what());
    }
}

bool InstagramOAuth::hasValidToken()
{
    std::string token = loadAccessToken();
    return !token.empty() && !isTokenExpired(token);
}

std::string InstagramOAuth::getAccessToken()
{
    return loadAccessToken();
}

bool InstagramOAuth::isTokenExpired(const std::string& token)
{
    // Instagram tokens typically expire after 60 days
    // For now, we'll assume tokens are valid if they exist
    // In a production app, you'd want to check the actual expiration
    return token.empty();
}

std::string InstagramOAuth::getTokenExpirationDate(const std::string& token)
{
    // This would need to be implemented based on Instagram's token response
    // For now, return empty string
    return "";
}

} // namespace ci 