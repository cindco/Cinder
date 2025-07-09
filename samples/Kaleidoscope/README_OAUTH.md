# Instagram OAuth Authentication for Kaleidoscope

This guide explains how to set up Instagram OAuth authentication to use real Instagram photos in the Kaleidoscope sample.

## Prerequisites

1. **Instagram Developer Account**: You need to create an Instagram app at [Instagram Basic Display](https://developers.facebook.com/docs/instagram-basic-display-api/getting-started)

2. **Instagram App Setup**:
   - Go to [Facebook Developers](https://developers.facebook.com/)
   - Create a new app or use an existing one
   - Add Instagram Basic Display product
   - Configure your app with the following settings:
     - Valid OAuth Redirect URIs: `http://localhost:8080/callback`
     - App Domains: `localhost`
     - Privacy Policy URL: (your privacy policy URL)

## Setup Instructions

### Step 1: Get Your Instagram App Credentials

1. In your Facebook Developer Console, go to your app
2. Navigate to Instagram Basic Display > Basic Display
3. Note down your **Instagram App ID** and **Instagram App Secret**

### Step 2: Configure the OAuth Helper

1. Open `samples/Kaleidoscope/src/InstagramOAuthHelper.cpp`
2. Replace the placeholder values:
   ```cpp
   mClientId = "YOUR_INSTAGRAM_CLIENT_ID";        // Your Instagram App ID
   mClientSecret = "YOUR_INSTAGRAM_CLIENT_SECRET"; // Your Instagram App Secret
   ```

### Step 3: Build and Run the OAuth Helper

1. Build the project:
   ```bash
   cd samples/Kaleidoscope/proj/cmake/build
   cmake ..
   cmake --build . --config Release
   ```

2. Run the OAuth Helper:
   ```bash
   ./InstagramOAuthHelper/Release/InstagramOAuthHelper.exe
   ```

### Step 4: Complete OAuth Flow

1. **Start OAuth Flow**: Press 'S' in the OAuth Helper app
   - The authorization URL will be copied to your clipboard
   - The URL will also be displayed in the app window

2. **Authorize in Browser**: 
   - Open the authorization URL in your browser
   - Log in to Instagram if prompted
   - Grant permissions to your app
   - You'll be redirected to a URL like: `http://localhost:8080/callback?code=AQD...`

3. **Extract Authorization Code**:
   - Copy the `code` parameter from the redirect URL
   - The code looks like: `AQD...` (long string)

4. **Exchange Code for Token**: 
   - Paste the authorization code into your clipboard
   - Press 'E' in the OAuth Helper app
   - The app will exchange the code for an access token and save it

### Step 5: Run Kaleidoscope with Real Instagram Photos

1. The access token is automatically saved to `instagram_tokens.txt`
2. Run the main Kaleidoscope app:
   ```bash
   ./Kaleidoscope/Release/Kaleidoscope.exe
   ```
3. The app will automatically detect and use the stored access token
4. You should now see real Instagram photos in the kaleidoscope effect!

## Troubleshooting

### Common Issues

1. **"Invalid redirect URI" error**:
   - Make sure your redirect URI in the Facebook Developer Console exactly matches: `http://localhost:8080/callback`

2. **"Invalid client_id" error**:
   - Double-check your Instagram App ID in the OAuth Helper code

3. **"Invalid authorization code" error**:
   - Make sure you're copying the entire code from the redirect URL
   - Codes expire quickly, so exchange them immediately

4. **"Access token expired" error**:
   - Press 'C' in the OAuth Helper to clear tokens
   - Repeat the OAuth flow to get a new token

### Token Management

- **Clear tokens**: Press 'C' in the OAuth Helper
- **Check stored tokens**: Look for `instagram_tokens.txt` in the app directory
- **Manual token editing**: You can manually edit `instagram_tokens.txt` if needed

## Security Notes

- **Never commit tokens to version control**: The `instagram_tokens.txt` file should be in your `.gitignore`
- **Keep your client secret secure**: Don't share your Instagram App Secret
- **Token expiration**: Instagram access tokens expire after 60 days, you'll need to refresh them

## API Limitations

- **Rate limits**: Instagram has rate limits on API calls
- **Media access**: You can only access media from users who have authorized your app
- **Permissions**: The app requests `user_profile` and `user_media` permissions

## Demo Mode

If you don't want to set up OAuth authentication, the app will automatically run in demo mode using random images from Lorem Picsum. This is perfect for testing and development.

## Support

For issues with Instagram API:
- [Instagram Basic Display API Documentation](https://developers.facebook.com/docs/instagram-basic-display-api)
- [Facebook Developers Support](https://developers.facebook.com/support/)

For issues with the Kaleidoscope sample:
- Check the Cinder documentation and forums
- Review the console output for error messages 