if(NOT TARGET Cairo)
add_library(Cairo STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/src/Cairo.cpp
)

# Common include directories
# (Add platform-specific includes below if needed)
target_include_directories(Cairo PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/include
    ${CMAKE_CURRENT_LIST_DIR}/../../../../include
    ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/include/cinder
    ${CMAKE_SOURCE_DIR}/include/freetype/include
)

# Platform-specific configuration
if(WIN32)
    # Windows: Use bundled static libraries and MSW headers
    target_include_directories(Cairo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/include/msw
    )
    target_link_libraries(Cairo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/lib/msw/x64/cairo-static.lib
        ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/lib/msw/x64/pixman-1.lib
        gdi32
        user32
    )
elseif(APPLE)
    # macOS: Use bundled static libraries and macOS headers
    target_include_directories(Cairo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/include/macosx
    )
    target_link_libraries(Cairo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/lib/macosx/libcairo.a
        ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/lib/macosx/libpixman-1.a
        ${CMAKE_CURRENT_LIST_DIR}/../../../Cairo/lib/macosx/libpng16.a
    )
elseif(UNIX AND NOT APPLE AND NOT ANDROID)
    # Linux: Use system-installed libraries via pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(CAIRO REQUIRED cairo)
    pkg_check_modules(PIXMAN REQUIRED pixman-1)
    pkg_check_modules(PNG REQUIRED libpng)
    target_include_directories(Cairo PUBLIC
        ${CAIRO_INCLUDE_DIRS}
        ${PIXMAN_INCLUDE_DIRS}
        ${PNG_INCLUDE_DIRS}
    )
    target_link_libraries(Cairo PUBLIC
        ${CAIRO_LIBRARIES}
        ${PIXMAN_LIBRARIES}
        ${PNG_LIBRARIES}
    )
elseif(ANDROID)
    # Android: Placeholder for future support
    message(WARNING "Cairo block: Android support is not fully implemented. Please add the appropriate include directories and libraries for your Android build.")
    # Example:
    # target_include_directories(Cairo PUBLIC <android-cairo-includes>)
    # target_link_libraries(Cairo PUBLIC <android-cairo-libs>)
endif()
endif() 