cmake_minimum_required( VERSION 3.10 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )

project( InstagramOAuth )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." ABSOLUTE )
get_filename_component( BLOCK_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

if(NOT TARGET InstagramOAuth)
    file(GLOB_RECURSE INSTAGRAMOAUTH_SOURCES "${CMAKE_CURRENT_LIST_DIR}/../../src/*.cpp")
    if(INSTAGRAMOAUTH_SOURCES)
        add_library(InstagramOAuth STATIC ${INSTAGRAMOAUTH_SOURCES})
        target_include_directories(InstagramOAuth PUBLIC
            "${CMAKE_CURRENT_LIST_DIR}/../../include"
            "${CMAKE_SOURCE_DIR}/include"
            "${CMAKE_SOURCE_DIR}/include/nlohmann"
        )
        
        # Link against Cinder libraries
        target_link_libraries(InstagramOAuth ${CINDER_LIBS})
    else()
        message(FATAL_ERROR "No source files found for InstagramOAuth block!")
    endif()
endif()

# Build the OAuth Helper sample app
ci_make_app(
    TARGET_NAME InstagramOAuthHelperApp
    SOURCES     ${BLOCK_PATH}/src/InstagramOAuthHelperApp.cpp
    CINDER_PATH ${CINDER_PATH}
    INCLUDES    ${BLOCK_PATH}/include
    BLOCKS      InstagramOAuth
) 