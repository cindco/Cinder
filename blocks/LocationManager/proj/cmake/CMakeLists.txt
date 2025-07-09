if(APPLE)
if(NOT TARGET LocationManager)
add_library(LocationManager STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../LocationManager/src/cinder/LocationManager.cpp
)
target_include_directories(LocationManager PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../LocationManager/src/cinder
    ${CMAKE_CURRENT_LIST_DIR}/../../../../include
)
endif()
endif() 