cmake_minimum_required( VERSION 3.10 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

if(WIN32)
    string(SUBSTRING "${CMAKE_SOURCE_DIR}" 0 1 drive_letter)
    execute_process(
        COMMAND powershell -Command "(Get-Volume -DriveLetter ${drive_letter}).FileSystem"
        OUTPUT_VARIABLE fsinfo
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    string(FIND "${fsinfo}" "exFAT" exfat_found)
    if(NOT exfat_found EQUAL -1)
        message(WARNING "exFAT filesystem detected. Assets will be copied instead of symlinked.")
        set(CINDER_COPY_ASSETS ON CACHE BOOL "Copy assets instead of symlinking on exFAT" FORCE)
    endif()
endif()

# Configure the Android toolchain before the project start
if( CINDER_TARGET )
	string( TOLOWER "${CINDER_TARGET}" CINDER_TARGET_LOWER )
	if( "android" STREQUAL "${CINDER_TARGET_LOWER}" )
	    include( "${CMAKE_CURRENT_SOURCE_DIR}/proj/cmake/modules/cinderAndroidToolchain.cmake" )
    endif()
endif()

# Project start
project( cinder )

# Enforce C++17 standard for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option( CINDER_BUILD_TESTS "Build unit tests." OFF )
option( CINDER_BUILD_ALL_SAMPLES "Build all samples." OFF )
set( CINDER_BUILD_SAMPLE "" CACHE STRING "Build a specific sample by specifying its path relative to the samples directory (ex. '_opengl/Cube')." )

set( CINDER_PATH      "${CMAKE_CURRENT_SOURCE_DIR}" )
set( CINDER_CMAKE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/proj/cmake" )

include( ${CINDER_CMAKE_DIR}/configure.cmake )
include( ${CINDER_CMAKE_DIR}/libcinder_configure.cmake )
include( ${CINDER_CMAKE_DIR}/libcinder_source_files.cmake )

set( CINDER_SKIP_SAMPLES "" )

if( CINDER_LINUX )
	include( "${CINDER_CMAKE_DIR}/platform_linux.cmake" )
elseif( CINDER_MAC )
	include( "${CINDER_CMAKE_DIR}/platform_macosx.cmake" )
elseif( CINDER_ANDROID )
	include( "${CINDER_CMAKE_DIR}/platform_android.cmake" )
elseif( CINDER_MSW )
	include( "${CINDER_CMAKE_DIR}/platform_msw.cmake" )
else()
	message( FATAL_ERROR "no target defined for system: '${CMAKE_SYSTEM_NAME}.'" )
endif()

include( ${CINDER_CMAKE_DIR}/libcinder_target.cmake )

if( CINDER_BUILD_ALL_SAMPLES )
	include( ${CINDER_CMAKE_DIR}/modules/findCMakeDirs.cmake )

	set( allSamples "" )
	findCMakeDirs( allSamples "${CINDER_PATH}/samples" "${CINDER_SKIP_SAMPLES}" )

	foreach( sampleDir ${allSamples} )
		ci_log_v( "adding sample: ${sampleDir}" )
		add_subdirectory( ${sampleDir} )
	endforeach()
elseif( CINDER_BUILD_SAMPLE )
	foreach( sampleDir ${CINDER_BUILD_SAMPLE} )
		ci_log_v( "adding sample: ${sampleDir}" )
		add_subdirectory( ${CINDER_PATH}/samples/${sampleDir}/proj/cmake )
	endforeach()
endif()

if( CINDER_BUILD_TESTS )
	enable_testing()
	add_subdirectory( ${CINDER_PATH}/test/unit/proj/cmake )
	add_custom_target( check COMMAND ${CMAKE_CTEST_COMMAND} --verbose )
endif()
