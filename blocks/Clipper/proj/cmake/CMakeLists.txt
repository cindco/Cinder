if(NOT TARGET Clipper)
add_library(Clipper STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../Clipper/src/CinderClipper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../../Clipper/src/clipper.cpp
)
target_include_directories(Clipper PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../Clipper/include
    ${CMAKE_CURRENT_LIST_DIR}/../../../../include
)
endif() 