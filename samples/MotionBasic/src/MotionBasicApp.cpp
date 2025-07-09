#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Camera.h"
#include "cinder/Timeline.h"
#if defined( CINDER_COCOA_TOUCH ) || defined( CINDER_ANDROID )
#include "cinder/MotionManager.h"
#endif
#include "cinder/Log.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;

class MotionBasicApp : public App {
  public:
	virtual void	setup();
	virtual void	update();
	virtual void	draw();
	
	mat4			mModelMatrix;
	CameraPersp		mCam;
	Anim<Color>		mBackgroundColor;
};

void MotionBasicApp::setup()
{
#if defined( CINDER_COCOA_TOUCH ) || defined( CINDER_ANDROID )
	CI_LOG_V( "gyro available: " << MotionManager::isGyroAvailable() );
	MotionManager::enable( 60.0f/*, MotionManager::SensorMode::Accelerometer*/ );
#endif
	mCam.setPerspective( 60, getWindowAspectRatio(), 1, 1000 );
	mCam.lookAt( vec3( 0, 0, 3 ), vec3( 0 ) );
}

void MotionBasicApp::update()
{
#if defined( CINDER_COCOA_TOUCH ) || defined( CINDER_ANDROID )
	if( ! MotionManager::isEnabled() )
		return;
	mModelMatrix = inverse( MotionManager::getRotationMatrix() );

	if( MotionManager::isShaking( 1.5f ) ) {
		CI_LOG_V( "isShaking!" );
		mBackgroundColor = Color::gray( MotionManager::getShakeDelta() / 10.0f );
		timeline().apply( &mBackgroundColor, Color::black(), 0.5f, EaseInQuad() );
	}
#else
	// Desktop fallback: static model matrix and background color
	mModelMatrix = mat4();
	// Optionally animate or set mBackgroundColor here if desired
#endif
}

void MotionBasicApp::draw()
{
	gl::clear( mBackgroundColor() );
	gl::enableDepthRead();

	gl::setMatrices( mCam );
	gl::multModelMatrix( mModelMatrix );

	gl::drawCoordinateFrame();
//	gl::drawColorCube( vec3::zero(), vec3( 1, 1, 1 ) );
}

CINDER_APP( MotionBasicApp, RendererGl )
