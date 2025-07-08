#pragma once

#include "cinder/Json.h"
#include <string>
#include <memory>
#include <thread>
#include "cinder/Surface.h"
#include "cinder/ConcurrentCircularBuffer.h"

class Instagram {
public:
    Instagram() {}
    Instagram(const std::string &user, const std::string &imageUrl, const ci::Surface &image)
        : mUser(user), mImageUrl(imageUrl), mImage(image) {}
    std::string mUser, mImageUrl;
    ci::Surface mImage;
};

class InstagramStream {
public:
    InstagramStream(const std::string &clientId);
    InstagramStream(const std::string &searchPhrase, const std::string &clientId);
    InstagramStream(const std::string &searchPhrase, const int &minId, const int &maxId, const std::string &clientId);
    InstagramStream(ci::vec2 loc, float dist, int minTs, int maxTs, std::string clientId);
    InstagramStream(ci::vec2 loc, float dist, std::string clientId);
    InstagramStream(ci::vec2 loc, std::string clientId);
    ~InstagramStream();

    bool hasInstagramAvailable();
    Instagram getNextInstagram();
    bool isConnected();

protected:
    void startThread(std::string url);
    void serviceGrams(std::string url);

    std::string mSearchPhrase, mClientId;
    std::shared_ptr<std::thread> mThread;
    ci::ConcurrentCircularBuffer<Instagram> mBuffer;
    bool mCanceled = false;
    bool mIsConnected = false;
};

ci::JsonTree queryInstagram(const std::string &searchUrl); 