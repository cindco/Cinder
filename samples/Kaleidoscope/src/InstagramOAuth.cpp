#include "InstagramOAuth.h"
#include "cinder/Utilities.h"
#include "cinder/Log.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <httplib.h>

using namespace ci;

const std::string InstagramOAuth::INSTAGRAM_AUTH_URL = "https://api.instagram.com/oauth/authorize";
const std::string InstagramOAuth::INSTAGRAM_TOKEN_URL = "https://api.instagram.com/oauth/access_token";
const std::string InstagramOAuth::TOKEN_FILE_NAME = "instagram_tokens.txt";

std::string InstagramOAuth::getAuthUrl(const std::string& clientId, const std::string& redirectUri)
{
    std::string authUrl = INSTAGRAM_AUTH_URL + "?client_id=" + clientId +
                          "&redirect_uri=" + ci::Url::encode(redirectUri) +
                          "&scope=user_profile,user_media" +
                          "&response_type=code";
    return authUrl;
}

std::string InstagramOAuth::exchangeCodeForToken(const std::string& clientId, const std::string& clientSecret, 
                                                const std::string& code, const std::string& redirectUri)
{
    try {
        httplib::Client cli("https://api.instagram.com");
        httplib::Params params = {
            {"client_id", clientId},
            {"client_secret", clientSecret},
            {"grant_type", "authorization_code"},
            {"redirect_uri", redirectUri},
            {"code", code}
        };
        auto res = cli.Post("/oauth/access_token", params);
        if (res && res->status == 200) {
            auto jsonResponse = nlohmann::json::parse(res->body);
            if (jsonResponse.contains("access_token")) {
                std::string accessToken = jsonResponse["access_token"].get<std::string>();
                std::string refreshToken = "";
                if (jsonResponse.contains("refresh_token")) {
                    refreshToken = jsonResponse["refresh_token"].get<std::string>();
                }
                saveAccessToken(accessToken, refreshToken);
                return accessToken;
            } else {
                CI_LOG_E("Failed to exchange code for token: " << res->body);
                return "";
            }
        } else {
            CI_LOG_E("HTTP error in exchangeCodeForToken: " << (res ? std::to_string(res->status) : "no response"));
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
        httplib::Client cli("https://api.instagram.com");
        httplib::Params params = {
            {"client_id", clientId},
            {"client_secret", clientSecret},
            {"grant_type", "refresh_token"},
            {"refresh_token", refreshToken}
        };
        auto res = cli.Post("/oauth/access_token", params);
        if (res && res->status == 200) {
            auto jsonResponse = nlohmann::json::parse(res->body);
            if (jsonResponse.contains("access_token")) {
                std::string accessToken = jsonResponse["access_token"].get<std::string>();
                std::string newRefreshToken = refreshToken;
                if (jsonResponse.contains("refresh_token")) {
                    newRefreshToken = jsonResponse["refresh_token"].get<std::string>();
                }
                saveAccessToken(accessToken, newRefreshToken);
                return accessToken;
            } else {
                CI_LOG_E("Failed to refresh token: " << res->body);
                return "";
            }
        } else {
            CI_LOG_E("HTTP error in refreshAccessToken: " << (res ? std::to_string(res->status) : "no response"));
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
                    return line.substr(13);
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
                    return line.substr(14);
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
    return token.empty();
}

std::string InstagramOAuth::getTokenExpirationDate(const std::string& token)
{
    return "";
} 