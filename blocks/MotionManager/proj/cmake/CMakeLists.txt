if(APPLE OR CINDER_ANDROID)
    if(NOT TARGET MotionManager)
        add_library(MotionManager STATIC
            ${CMAKE_CURRENT_LIST_DIR}/../../../MotionManager/src/cinder/MotionManager.cpp
            ${CMAKE_CURRENT_LIST_DIR}/../../../MotionManager/src/cinder/MotionImplAndroid.cpp
            ${CMAKE_CURRENT_LIST_DIR}/../../../MotionManager/src/cinder/MotionImplCoreMotion.mm
        )
        target_include_directories(MotionManager PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/../../../MotionManager/src/cinder
            ${CMAKE_CURRENT_LIST_DIR}/../../../../include
        )
    endif()
endif() 