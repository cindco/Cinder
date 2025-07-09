#pragma once

#include "cinder/app/App.h"
#include "cinder/Surface.h"
#include "cinder/ConcurrentCircularBuffer.h"
#include "cinder/Thread.h"
#include <string>
#include <memory>

namespace ci {

class Instagram {
public:
    Instagram() {}
    Instagram(const std::string& user, const std::string& imageUrl, const Surface& image)
        : mUser(user), mImageUrl(imageUrl), mImage(image) {}
    
    const std::string& getUser() const { return mUser; }
    const std::string& getImageUrl() const { return mImageUrl; }
    const Surface& getImage() const { return mImage; }
    bool isNull() const { return mImageUrl.empty(); }
    
private:
    std::string mUser, mImageUrl;
    Surface mImage;
};

class InstagramStream {
public:
    // Popular images
    InstagramStream(const std::string& clientId);
    
    // Images with a specific tag
    InstagramStream(const std::string& searchPhrase, const std::string& clientId);
    InstagramStream(const std::string& searchPhrase, const int& minId, const int& maxId, const std::string& clientId);
    
    // Search for media in a given area
    InstagramStream(vec2 loc, float dist, int minTs, int maxTs, std::string clientId);
    InstagramStream(vec2 loc, float dist, std::string clientId);
    InstagramStream(vec2 loc, std::string clientId);
    
    ~InstagramStream();
    
    bool hasInstagramAvailable();
    Instagram getNextInstagram();
    bool isConnected();
    bool isDemoMode();
    
protected:
    void startThread(std::string url);
    void startDemoThread();
    void serviceGrams(std::string url);
    void serviceDemoGrams();
    
    std::string mSearchPhrase;
    std::shared_ptr<std::thread> mThread;
    ConcurrentCircularBuffer<Instagram> mBuffer;
    bool mCanceled;
    bool mIsConnected;
    std::string mClientId;
    bool mDemoMode;
};

} // namespace ci 