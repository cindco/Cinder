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
#include <nlohmann/json.hpp>

#include "InstagramStream.h"

static const int BUFFER_SIZE = 10;

using namespace std;
using namespace ci;
using namespace ci::app;

static const string INSTAGRAM_API_URL = "https://api.instagram.com/v1";

nlohmann::json queryInstagram(const std::string &searchUrl)
{
    Url url(searchUrl, true);
    auto data = loadUrl(url);
    std::stringstream buffer;
    buffer << data->stream()->rdbuf();
    return nlohmann::json::parse(buffer.str());
}


InstagramStream::InstagramStream(const string &clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mClientId( clientId )
{
	startThread(INSTAGRAM_API_URL + "/media/popular?client_id="+ mClientId);
}

InstagramStream::InstagramStream( const std::string &searchPhrase, const string &clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mSearchPhrase( searchPhrase ),
mClientId( clientId )
{
	startThread(INSTAGRAM_API_URL + "/tags/" + Url::encode( mSearchPhrase ) + "/media/recent?client_id="+ mClientId);
}

InstagramStream::InstagramStream(const std::string &searchPhrase, const int &minId, const int &maxId, const std::string &clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mSearchPhrase( searchPhrase ),
mClientId( clientId )
{
	startThread(INSTAGRAM_API_URL + "/tags/" + Url::encode( mSearchPhrase ) + "/media/recent?client_id="+ mClientId + "&min_id=" + toString(minId) + "&max_id=" + toString(maxId));
}


InstagramStream::InstagramStream(ci::vec2 loc, float dist, int minTs, int maxTs, std::string clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mClientId( clientId )
{
	startThread(INSTAGRAM_API_URL + "/media/search?lat=" + toString(loc.x) + "&lng=" + toString(loc.y) + "&distance=" + toString(dist) + "&min_timestamp=" + toString(minTs) + "&max_timestamp=" + toString(maxTs) + "&client_id="+ mClientId);
}

InstagramStream::InstagramStream(ci::vec2 loc, float dist, std::string clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mClientId( clientId )
{
	startThread(INSTAGRAM_API_URL + "/media/search?lat=" + toString(loc.x) + "&lng=" + toString(loc.y) + "&distance=" + toString(dist) + "&client_id="+ mClientId);
}

InstagramStream::InstagramStream(ci::vec2 loc, std::string clientId )
: mBuffer( BUFFER_SIZE ), // our buffer of instagrams can hold up to 10
mCanceled( false ),
mClientId( clientId )
{
	startThread(INSTAGRAM_API_URL + "/media/search?lat=" + toString(loc.x) + "&lng=" + toString(loc.y) + "&client_id="+ mClientId);
}

void InstagramStream::startThread(string url){
	mThread = make_shared<thread>( bind( &InstagramStream::serviceGrams, this, url ) );
}

InstagramStream::~InstagramStream()
{
	mCanceled = true;
	mBuffer.cancel();
	mThread->join();
}

// Non-autenticated queries
// X	search for recent images of a certain tag
// X	get popular images	
// _	search for users with by user id							https://api.instagram.com/v1/users/search?q=userId&client_id=xxx
// _	get info about a user										https://api.instagram.com/v1/users/1574083/?client_id=xxx
// _	see who a user follows										https://api.instagram.com/v1/users/1574083/follows?client_id=xxx
// _	see who a user follows										https://api.instagram.com/v1/users/1574083/followed-by?client_id=xxx
// _	Get information about a media object.						https://api.instagram.com/v1/media/3/?client_id=xxx
// X	Search for media in a given area.							https://api.instagram.com/v1/media/search?lat=48.858844&lng=2.294351&client_id=xxx
// _	Get comments of a speficic media							https://api.instagram.com/v1/media/555/comments?client_id=xxx
// _	Get likes of a speficic media								https://api.instagram.com/v1/media/555/likes?client_id=xxx
// _	Get information about a tag object.							https://api.instagram.com/v1/tags/nofilter?client_id=xxx
// _	Get information about a location							https://api.instagram.com/v1/locations/1?client_id=xxx
// _	Get a list of recent media objects from a given location.	https://api.instagram.com/v1/tags/snow/media/recent?client_id=xxx
// _	Search for a location by geographic coordinate.				https://api.instagram.com/v1/locations/search?lat=48.858844&lng=2.294351&client_id=xxx


// Function the background thread lives in
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
                CI_LOG_W("exception caught, what: " << exc.what());
                // Optionally log queryResult and nextQueryString
                if (queryResult.contains("meta") && queryResult["meta"].contains("code") && queryResult["meta"]["code"].get<std::string>() == "420") {
                    console() << "420 error" << std::endl;
                    mIsConnected = false;
                }
                ci::sleep(1000); // try again in 1 second
            }
        }
        if (resultIt != searchResults.end()) {
            try {
                std::string userName = (*resultIt)["user"]["username"].get<std::string>();
                std::string imageUrl = (*resultIt)["images"]["standard_resolution"]["url"].get<std::string>();
                Surface image(loadImage(loadUrl(imageUrl)));
                mBuffer.pushFront(Instagram(userName, imageUrl, image));
            }
            catch (const std::exception &exc) {
                CI_LOG_W("exception caught, what: " << exc.what());
            }
            ++resultIt;
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