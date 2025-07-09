if(NOT TARGET MotionManager)
file(GLOB MOTIONMANAGER_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/../../../MotionManager/src/cinder/*.cpp
)
add_library(MotionManager STATIC ${MOTIONMANAGER_SOURCES})
target_include_directories(MotionManager PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../MotionManager/src/cinder
    ${CMAKE_CURRENT_LIST_DIR}/../../../../include
)
endif() 