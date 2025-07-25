//
//	InstagramStream.h
//	InstagramTest
//
//	Created by Greg Kepler on 6/9/12.
//	Copyright (c) 2012 The Barbarian Group. All rights reserved.
//


#pragma once

#include "cinder/app/App.h"
#include "cinder/Surface.h"
#include "cinder/ConcurrentCircularBuffer.h"
#include "cinder/Thread.h"
#include "cinder/Vector.h"
#include <string>
#include <memory>
#include <vector>
#include <thread>

class Instagram {
public:
    Instagram() {}
    Instagram(const std::string& user, const std::string& imageUrl, const ci::Surface& image)
        : mUser(user), mImageUrl(imageUrl), mImage(image) {}
    const std::string& getUser() const { return mUser; }
    const std::string& getImageUrl() const { return mImageUrl; }
    const ci::Surface& getImage() const { return mImage; }
    bool isNull() const { return mImageUrl.empty(); }
private:
    std::string mUser, mImageUrl;
    ci::Surface mImage;
};

class InstagramStream {
public:
    InstagramStream(const std::string& clientId);
    InstagramStream(const std::string& searchPhrase, const std::string& clientId);
    InstagramStream(const std::string& searchPhrase, const int& minId, const int& maxId, const std::string& clientId);
    InstagramStream(const glm::vec2& loc, float dist, int minTs, int maxTs, std::string clientId);
    InstagramStream(const glm::vec2& loc, float dist, std::string clientId);
    InstagramStream(const glm::vec2& loc, std::string clientId);
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
    ci::ConcurrentCircularBuffer<Instagram> mBuffer;
    bool mCanceled;
    bool mIsConnected;
    std::string mClientId;
    bool mDemoMode;
};