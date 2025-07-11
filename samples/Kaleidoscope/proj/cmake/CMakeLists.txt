cmake_minimum_required( VERSION 3.10 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

# Force MSVC to use the dynamic runtime (/MD)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL" CACHE STRING "" FORCE)

project( Kaleidoscope )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

ci_make_app(
    SOURCES     ${APP_PATH}/src/InstascopeApp.cpp
                ${APP_PATH}/src/TextRibbon.cpp
                ${APP_PATH}/src/TrianglePiece.cpp
                ${APP_PATH}/src/InstagramOAuth.cpp
                ${APP_PATH}/src/InstagramStream.cpp
    INCLUDES    ${APP_PATH}/include
    CINDER_PATH ${CINDER_PATH}
)

# Force the app target to use the dynamic runtime (/MD)
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
