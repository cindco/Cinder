//
//	InstagramOAuthHelperApp.cpp
//	Instagram OAuth Helper for InstagramOAuth Block
//
//	Created for Instagram Basic Display API OAuth flow
//

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"
#include "cinder/Utilities.h"
#include "InstagramOAuth.h"

using namespace ci;
using namespace ci::app;

class InstagramOAuthHelperApp : public App {
public:
    void setup() override;
    void draw() override;
    void keyDown(KeyEvent event) override;
    
private:
    void startOAuthFlow();
    void handleAuthorizationCode(const std::string& code);
    void displayInstructions();
    
    std::string mClientId;
    std::string mClientSecret;
    std::string mRedirectUri;
    std::string mAuthUrl;
    bool mWaitingForCode;
    std::string mStatusMessage;
};

void InstagramOAuthHelperApp::setup()
{
    setWindowSize(800, 600);
    setFrameRate(30);
    
    // Instagram App credentials - Replace with your own
    mClientId = "YOUR_INSTAGRAM_CLIENT_ID";
    mClientSecret = "YOUR_INSTAGRAM_CLIENT_SECRET";
    mRedirectUri = "http://localhost:8080/callback";
    
    mWaitingForCode = false;
    mStatusMessage = "Press 'S' to start OAuth flow, 'C' to clear tokens, 'Q' to quit";
    
    console() << "Instagram OAuth Helper" << std::endl;
    console() << "=====================" << std::endl;
    console() << "1. Set your Instagram Client ID and Secret in the code" << std::endl;
    console() << "2. Press 'S' to start OAuth flow" << std::endl;
    console() << "3. Copy the authorization code from the browser" << std::endl;
    console() << "4. Press 'E' to exchange code for token" << std::endl;
    console() << "5. Use the generated token in Kaleidoscope" << std::endl;
}

void InstagramOAuthHelperApp::draw()
{
    gl::clear(Color(0.1f, 0.1f, 0.1f));
    
    gl::drawString("Instagram OAuth Helper", vec2(20, 20), Color::white(), Font("Arial", 24));
    gl::drawString(mStatusMessage, vec2(20, 60), Color::white(), Font("Arial", 14));
    
    if (!mAuthUrl.empty()) {
        gl::drawString("Auth URL:", vec2(20, 100), Color::yellow(), Font("Arial", 12));
        gl::drawString(mAuthUrl, vec2(20, 120), Color::white(), Font("Arial", 10));
    }
    
    gl::drawString("Controls:", vec2(20, 200), Color::cyan(), Font("Arial", 12));
    gl::drawString("S - Start OAuth flow", vec2(20, 220), Color::white(), Font("Arial", 10));
    gl::drawString("E - Exchange code for token", vec2(20, 240), Color::white(), Font("Arial", 10));
    gl::drawString("C - Clear stored tokens", vec2(20, 260), Color::white(), Font("Arial", 10));
    gl::drawString("Q - Quit", vec2(20, 280), Color::white(), Font("Arial", 10));
}

void InstagramOAuthHelperApp::keyDown(KeyEvent event)
{
    switch (event.getCode()) {
        case KeyEvent::KEY_s:
        case KeyEvent::KEY_S:
            startOAuthFlow();
            break;
            
        case KeyEvent::KEY_e:
        case KeyEvent::KEY_E:
            if (mWaitingForCode) {
                std::string code = getClipboardText();
                if (!code.empty()) {
                    handleAuthorizationCode(code);
                } else {
                    mStatusMessage = "No code in clipboard. Copy the code from browser first.";
                }
            } else {
                mStatusMessage = "Start OAuth flow first (press 'S')";
            }
            break;
            
        case KeyEvent::KEY_c:
        case KeyEvent::KEY_C:
            InstagramOAuth::clearStoredTokens();
            mStatusMessage = "Stored tokens cleared";
            break;
            
        case KeyEvent::KEY_q:
        case KeyEvent::KEY_Q:
            quit();
            break;
    }
}

void InstagramOAuthHelperApp::startOAuthFlow()
{
    if (mClientId == "YOUR_INSTAGRAM_CLIENT_ID") {
        mStatusMessage = "ERROR: Set your Instagram Client ID and Secret in the code first!";
        return;
    }
    
    mAuthUrl = InstagramOAuth::getAuthUrl(mClientId, mRedirectUri);
    mWaitingForCode = true;
    
    // Copy auth URL to clipboard
    setClipboardText(mAuthUrl);
    
    mStatusMessage = "Auth URL copied to clipboard. Open in browser, authorize, and copy the code.";
    console() << "Authorization URL: " << mAuthUrl << std::endl;
    console() << "1. Open this URL in your browser" << std::endl;
    console() << "2. Authorize the application" << std::endl;
    console() << "3. Copy the authorization code from the redirect URL" << std::endl;
    console() << "4. Press 'E' to exchange the code for an access token" << std::endl;
}

void InstagramOAuthHelperApp::handleAuthorizationCode(const std::string& code)
{
    console() << "Exchanging code for token..." << std::endl;
    
    std::string accessToken = InstagramOAuth::exchangeCodeForToken(mClientId, mClientSecret, code, mRedirectUri);
    
    if (!accessToken.empty()) {
        mStatusMessage = "SUCCESS: Access token saved! You can now use it in Kaleidoscope.";
        console() << "Access token saved successfully!" << std::endl;
        console() << "You can now run Kaleidoscope with the stored token." << std::endl;
    } else {
        mStatusMessage = "ERROR: Failed to exchange code for token. Check console for details.";
        console() << "Failed to exchange code for token." << std::endl;
    }
    
    mWaitingForCode = false;
}

CINDER_APP(InstagramOAuthHelperApp, RendererGl) 