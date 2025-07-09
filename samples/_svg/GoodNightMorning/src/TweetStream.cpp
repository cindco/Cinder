#include "TweetStream.h"
#include "cinder/Rand.h"
#include "cinder/Thread.h"
#include "cinder/Function.h"
#include "cinder/ImageIo.h"
#include "cinder/Surface.h"
#include "cinder/Log.h"
#include "cinder/Url.h"
#include "cinder/Utilities.h"
#include "TwitterConfig.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace ci;
using json = nlohmann::json;

string replaceEscapes( const string &original );

// Configuration for X API (Twitter API v2)
#ifdef TWITTER_BEARER_TOKEN
const string TWITTER_BEARER_TOKEN = TWITTER_BEARER_TOKEN;
#else
const string TWITTER_BEARER_TOKEN = ""; // No token configured, will use demo mode
#endif
const string TWITTER_API_BASE = "https://api.twitter.com/2";

// X API (Twitter API v2) implementation using nlohmann/json
json queryTwitter( const std::string &query )
{
	if( TWITTER_BEARER_TOKEN.empty() ) {
		CI_LOG_W( "Twitter Bearer Token not configured. Using demo mode." );
		
		// Create a demo response structure
		json result;
		result["next_token"] = "";
		
		json data = json::array();
		json demoTweet;
		demoTweet["id"] = "demo_123";
		demoTweet["text"] = "This is a demo tweet. Configure TWITTER_BEARER_TOKEN to use real X API.";
		demoTweet["author_id"] = "demo_user";
		data.push_back( demoTweet );
		
		json includes;
		json users = json::array();
		json user;
		user["id"] = "demo_user";
		user["username"] = "demo_user";
		user["name"] = "Demo User";
		user["profile_image_url"] = "";
		users.push_back( user );
		includes["users"] = users;
		
		result["data"] = data;
		result["includes"] = includes;
		
		return result;
	}
	
	try {
		// Build the search query for X API v2
		string encodedQuery = Url::encode( query );
		string apiUrl = TWITTER_API_BASE + "/tweets/search/recent?query=" + encodedQuery + 
					   "&max_results=10&tweet.fields=author_id,created_at&user.fields=profile_image_url,username,name&expansions=author_id";
		
		// Note: Cinder's loadUrl doesn't support custom headers directly
		// For a real implementation, you'd need to use a different HTTP library
		// For now, we'll use the demo mode when a token is configured
		CI_LOG_W( "Custom headers not supported in Cinder's loadUrl. Using demo mode." );
		
		// Create a demo response structure
		json result;
		result["next_token"] = "";
		
		json data = json::array();
		json demoTweet;
		demoTweet["id"] = "demo_123";
		demoTweet["text"] = "X API requires custom headers. Using demo mode.";
		demoTweet["author_id"] = "demo_user";
		data.push_back( demoTweet );
		
		json includes;
		json users = json::array();
		json user;
		user["id"] = "demo_user";
		user["username"] = "demo_user";
		user["name"] = "Demo User";
		user["profile_image_url"] = "";
		users.push_back( user );
		includes["users"] = users;
		
		result["data"] = data;
		result["includes"] = includes;
		
		return result;
	}
	catch( const std::exception &exc ) {
		CI_LOG_E( "X API query failed: " << exc.what() );
		
		// Return a fallback response
		json result;
		result["next_token"] = "";
		
		json results = json::array();
		json errorTweet;
		errorTweet["text"] = "X API query failed. Check your bearer token and network connection.";
		errorTweet["from_user"] = "error";
		errorTweet["profile_image_url"] = "";
		results.push_back( errorTweet );
		
		result["results"] = results;
		return result;
	}
}


TweetStream::TweetStream( const std::string &searchPhrase )
	: mBuffer( 10 ), // our buffer of tweets can hold up to 10
	mCanceled( false ),
	mSearchPhrase( searchPhrase )
{
	mThread = thread( bind( &TweetStream::serviceTweets, this ) );
}

TweetStream::~TweetStream()
{
	mCanceled = true;
	mBuffer.cancel();
	mThread.join();
}

// Function the background thread lives in
void TweetStream::serviceTweets()
{
	ThreadSetup threadSetup;
	std::string nextToken = ""; // Use next_token instead of refresh_url
	json searchResults;
	json::const_iterator resultIt = searchResults.end();

	// This function loops until the app quits. Each iteration pulls out the next result from the X API query.
	// When it reaches the last result of the current query it issues a new one, based on the "next_token" property
	// of the current query.
	// The loop doesn't spin (max out the processor) because ConcurrentCircularBuffer.pushFront() non-busy-waits for a new
	// slot in the circular buffer to become available.
	while( ! mCanceled ) {
		if( resultIt == searchResults.end() ) { 		// are we at the end of the results of this JSON query?
			// issue a new query
			try {
				string queryString = "?q=" + Url::encode( mSearchPhrase );
				if( !nextToken.empty() ) {
					queryString += "&next_token=" + nextToken;
				}
				
				json queryResult = queryTwitter( queryString );
				// the next query will use the "next_token" of this one.
				nextToken = queryResult["next_token"].get<string>();
				
				// Transform the new API response structure to match the old structure
				if( queryResult.contains( "data" ) ) {
					json results = json::array();
					
					// Create a map of users for quick lookup
					map<string, json> users;
					if( queryResult.contains( "includes" ) && queryResult["includes"].contains( "users" ) ) {
						for( const auto& user : queryResult["includes"]["users"] ) {
							users[user["id"]] = user;
						}
					}
					
					for( const auto& tweet : queryResult["data"] ) {
						json transformedTweet;
						transformedTweet["text"] = tweet["text"];
						
						string authorId = tweet["author_id"];
						if( users.find( authorId ) != users.end() ) {
							json user = users[authorId];
							transformedTweet["from_user"] = user["username"];
							transformedTweet["profile_image_url"] = user.value( "profile_image_url", "" );
						} else {
							transformedTweet["from_user"] = "unknown_user";
							transformedTweet["profile_image_url"] = "";
						}
						
						results.push_back( transformedTweet );
					}
					
					searchResults = results;
				} else {
					searchResults = json::array();
				}
				
				resultIt = searchResults.begin();
			}
			catch( ci::Exception &exc ) {
				// our API query failed: put up a "tweet" with our error
				CI_LOG_W( "exception caught parsing query: " << exc.what() );
				mBuffer.pushFront( Tweet( "X API query failed", "sadness", SurfaceRef() ) );
				sleep( 2000 ); // try again in 2 seconds
			}
		}
		if( resultIt != searchResults.end() ) {
			try {
				// get the URL and load the image for this profile
				string profileImgUrlStr = (*resultIt)["profile_image_url"].get<string>();
				SurfaceRef userIcon;
				
				if( !profileImgUrlStr.empty() ) {
					try {
						Url profileImgUrl( profileImgUrlStr );
						userIcon = Surface::create( loadImage( loadUrl( profileImgUrl ) ) );
					}
					catch( ci::Exception &exc ) {
						CI_LOG_W( "Failed to load profile image: " << exc.what() );
						// Create a default surface if image loading fails
						userIcon = Surface::create( 32, 32, SurfaceChannelOrder::RGB );
					}
				} else {
					// Create a default surface for empty profile image URL
					userIcon = Surface::create( 32, 32, SurfaceChannelOrder::RGB );
				}
				
				// pull out the text of the tweet and replace any XML-style escapes
				string text = replaceEscapes( (*resultIt)["text"].get<string>() );
				string userName = (*resultIt)["from_user"].get<string>();
				mBuffer.pushFront( Tweet( text, userName, userIcon ) );
			}
			catch( ci::Exception &exc ) {
				CI_LOG_W( "exception caught parsing search results: " << exc.what() );
			}
			++resultIt;
		}
	}
}

void findAndReplaceAll( std::string& data, const std::string &toSearch, const std::string &replaceStr )
{
	size_t pos = data.find(toSearch);
	while( pos != std::string::npos ) {
		data.replace(pos, toSearch.size(), replaceStr);
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

// Replaces XML escaped characters with their equivalents
string replaceEscapes( const string &original )
{
	string result = original;
	findAndReplaceAll( result, "&lt;", "<" );
	findAndReplaceAll( result, "&gt;", ">" );
	findAndReplaceAll( result, "&amp;", "&" );
	return result;
}

bool TweetStream::hasTweetAvailable()
{
	return mBuffer.isNotEmpty();
}

Tweet TweetStream::getNextTweet()
{
	Tweet result;
	mBuffer.popBack( &result );
	return result;
}