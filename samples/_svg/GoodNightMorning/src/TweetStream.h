#pragma once

#include "cinder/Surface.h"
#include "cinder/ConcurrentCircularBuffer.h"
#include "cinder/Thread.h"

#include <string>

// X API (Twitter API v2) Configuration
// To use the real X API, you need to:
// 1. Go to https://developer.twitter.com/
// 2. Create a developer account and app
// 3. Get your Bearer Token
// 4. Set TWITTER_BEARER_TOKEN in TweetStream.cpp
// Note: The X API has rate limits and requires authentication

class Tweet {
  public:
	Tweet() {}
	Tweet( const std::string &phrase, const std::string &user, const ci::SurfaceRef &icon )
		: mPhrase( phrase ), mUser( user ), mIcon( icon )
	{}
  
	const std::string&		getPhrase() const { return mPhrase; }
	const std::string&		getUser() const { return mUser; }
	const ci::SurfaceRef&	getIcon() const { return mIcon; }
	
  private:
	std::string		mPhrase, mUser;
	ci::SurfaceRef	mIcon;
};

class TweetStream {
  public:
	TweetStream( const std::string &searchPhrase );
	~TweetStream();
	
	bool	hasTweetAvailable();
	Tweet	getNextTweet();

  protected:
	void	serviceTweets();

	std::string								mSearchPhrase;
	std::thread								mThread;
	ci::ConcurrentCircularBuffer<Tweet>		mBuffer;
	bool									mCanceled;
};