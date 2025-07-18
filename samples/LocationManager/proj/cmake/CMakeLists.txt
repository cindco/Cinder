if(APPLE)
    cmake_minimum_required( VERSION 3.10 FATAL_ERROR )
    set( CMAKE_VERBOSE_MAKEFILE ON )

    project( LocationManager )

    get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../.." ABSOLUTE )
    get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../" ABSOLUTE )

    include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

    file(GLOB SRC_FILES "${APP_PATH}/src/*.cpp")

    ci_make_app(
        APP_NAME    "LocationManagerApp"
        SOURCES     ${SRC_FILES}
        CINDER_PATH ${CINDER_PATH}
        INCLUDES    ${APP_PATH}/include
        BLOCKS      LocationManager
    )
endif()
