cmake_minimum_required( VERSION 3.10 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( opengl-ObjLoader )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../.." ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

ci_make_app(
	APP_NAME    "ObjLoader"
	CINDER_PATH ${CINDER_PATH}
	SOURCES     ${APP_PATH}/src/ObjLoaderApp.cpp
	INCLUDES    ${APP_PATH}/include
)
