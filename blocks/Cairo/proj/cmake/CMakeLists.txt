if(NOT TARGET Cairo)
add_library(Cairo STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/src/Cairo.cpp
)
target_include_directories(Cairo PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/include
    ${CMAKE_CURRENT_LIST_DIR}/../../../../include
    ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/include/cinder
    ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/include/msw
    ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/include/macosx
)
endif() 