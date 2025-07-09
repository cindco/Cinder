cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(InstagramOAuthHelperApp)
get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE)
include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")
ci_make_app(
    SOURCES     src/InstagramOAuthHelperApp.cpp
    CINDER_PATH ${CINDER_PATH}
    BLOCKS      InstagramOAuth
) 