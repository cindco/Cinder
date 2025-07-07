# Submodules configuration for Cinder
# This file configures external libraries as Git submodules

# Set submodule paths relative to Cinder root (self-contained approach)
set( CINDER_SUBMODULES_DIR "${CINDER_PATH}/include" )

# Configure ImGui submodule
ci_log_v( "Checking for ImGui submodule at: ${CINDER_SUBMODULES_DIR}/imgui" )
if( EXISTS "${CINDER_SUBMODULES_DIR}/imgui" )
    set( CINDER_IMGUI_DIR "${CINDER_SUBMODULES_DIR}/imgui" )
    list( APPEND CINDER_INCLUDE_USER_PRIVATE 
        ${CINDER_IMGUI_DIR}
        ${CINDER_IMGUI_DIR}/backends
        ${CINDER_IMGUI_DIR}/misc/freetype
        ${CINDER_IMGUI_DIR}/misc/cpp
    )
    list( APPEND CINDER_DEFINES "CINDER_IMGUI_EXTERNAL" )
    ci_log_v( "Using ImGui submodule from: ${CINDER_IMGUI_DIR}" )
else()
    message( FATAL_ERROR "ImGui submodule not found at ${CINDER_SUBMODULES_DIR}/imgui" )
endif()

# Configure GLFW submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/glfw" )
    set( CINDER_GLFW_DIR "${CINDER_SUBMODULES_DIR}/glfw" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_GLFW_DIR}/include )
    ci_log_v( "Using GLFW submodule from: ${CINDER_GLFW_DIR}" )
else()
    message( FATAL_ERROR "GLFW submodule not found at ${CINDER_SUBMODULES_DIR}/glfw" )
endif()

# Configure GLAD submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/glad" )
    set( CINDER_GLAD_DIR "${CINDER_SUBMODULES_DIR}/glad" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_GLAD_DIR}/include )
    ci_log_v( "Using GLAD submodule from: ${CINDER_GLAD_DIR}" )
else()
    message( FATAL_ERROR "GLAD submodule not found at ${CINDER_SUBMODULES_DIR}/glad" )
endif()

# Configure nlohmann/json submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/nlohmann" )
    set( CINDER_NLOHMANN_DIR "${CINDER_SUBMODULES_DIR}/nlohmann" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_NLOHMANN_DIR}/include )
    ci_log_v( "Using nlohmann/json submodule from: ${CINDER_NLOHMANN_DIR}" )
else()
    message( FATAL_ERROR "nlohmann/json submodule not found at ${CINDER_SUBMODULES_DIR}/nlohmann" )
endif()

# Configure GLM submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/glm" )
    set( CINDER_GLM_DIR "${CINDER_SUBMODULES_DIR}/glm" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_GLM_DIR} )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_GLM_DIR}/glm )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_GLM_DIR}/glm/glm )
    ci_log_v( "Using GLM submodule from: ${CINDER_GLM_DIR}" )
else()
    message( FATAL_ERROR "GLM submodule not found at ${CINDER_SUBMODULES_DIR}/glm" )
endif()

# Configure zlib submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/zlib" )
    set( CINDER_ZLIB_DIR "${CINDER_SUBMODULES_DIR}/zlib" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_ZLIB_DIR} )
    ci_log_v( "Using zlib submodule from: ${CINDER_ZLIB_DIR}" )
else()
    message( FATAL_ERROR "zlib submodule not found at ${CINDER_SUBMODULES_DIR}/zlib" )
endif()

# Configure FreeType submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/freetype" )
    set( CINDER_FREETYPE_DIR "${CINDER_SUBMODULES_DIR}/freetype" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_FREETYPE_DIR}/include )
    ci_log_v( "Using FreeType submodule from: ${CINDER_FREETYPE_DIR}" )
else()
    message( FATAL_ERROR "FreeType submodule not found at ${CINDER_SUBMODULES_DIR}/freetype" )
endif() 