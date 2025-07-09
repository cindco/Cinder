#pragma once

#include "cinder/app/App.h"
#include <string>

namespace ci {

// Instagram OAuth Authentication Helper
class InstagramOAuth {
public:
    // OAuth Authentication methods
    static std::string getAuthUrl(const std::string& clientId, const std::string& redirectUri);
    static std::string exchangeCodeForToken(const std::string& clientId, const std::string& clientSecret, 
                                           const std::string& code, const std::string& redirectUri);
    static std::string refreshAccessToken(const std::string& clientId, const std::string& clientSecret, 
                                        const std::string& refreshToken);
    
    // Token management
    static bool saveAccessToken(const std::string& accessToken, const std::string& refreshToken = "");
    static std::string loadAccessToken();
    static std::string loadRefreshToken();
    static void clearStoredTokens();
    static bool hasValidToken();
    static std::string getAccessToken();
    
    // Utility methods
    static bool isTokenExpired(const std::string& token);
    static std::string getTokenExpirationDate(const std::string& token);
    
private:
    static const std::string INSTAGRAM_AUTH_URL;
    static const std::string INSTAGRAM_TOKEN_URL;
    static const std::string TOKEN_FILE_NAME;
};

} // namespace ci 