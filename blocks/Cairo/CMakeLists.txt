cmake_minimum_required(VERSION 3.10)
project(CinderBlock-Cairo)

add_library(CinderBlock-Cairo STATIC src/Cairo.cpp)

# Include directories for Cairo and Cinder wrapper

target_include_directories(CinderBlock-Cairo PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/msw
    ${CMAKE_CURRENT_LIST_DIR}/include/cinder
)

if(WIN32)
    target_link_libraries(CinderBlock-Cairo
        PUBLIC
            ${CMAKE_CURRENT_LIST_DIR}/lib/msw/x64/cairo-static.lib
            ${CMAKE_CURRENT_LIST_DIR}/lib/msw/x64/pixman-1.lib
            gdi32
            user32
    )
endif() 