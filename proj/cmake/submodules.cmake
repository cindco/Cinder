# Submodules configuration for Cinder
# This file configures external libraries as Git submodules

# Set submodule paths relative to Cinder root
set( CINDER_SUBMODULES_DIR "${CINDER_PATH}/.." )

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
    # Fallback to bundled ImGui
    list( APPEND CINDER_INCLUDE_USER_PRIVATE ${CINDER_INC_DIR}/imgui )
    ci_log_v( "Using bundled ImGui" )
endif()

# Configure GLFW submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/glfw" )
    set( CINDER_GLFW_DIR "${CINDER_SUBMODULES_DIR}/glfw" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_GLFW_DIR}/include )
    ci_log_v( "Using GLFW submodule from: ${CINDER_GLFW_DIR}" )
else()
    # Fallback to bundled GLFW
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_INC_DIR}/glfw )
    ci_log_v( "Using bundled GLFW" )
endif()

# Configure GLAD submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/glad" )
    set( CINDER_GLAD_DIR "${CINDER_SUBMODULES_DIR}/glad" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_GLAD_DIR}/include )
    ci_log_v( "Using GLAD submodule from: ${CINDER_GLAD_DIR}" )
else()
    # Fallback to bundled GLAD
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_INC_DIR}/glad )
    ci_log_v( "Using bundled GLAD" )
endif()

# Configure nlohmann/json submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/nlohmann" )
    set( CINDER_NLOHMANN_DIR "${CINDER_SUBMODULES_DIR}/nlohmann" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_NLOHMANN_DIR}/include )
    ci_log_v( "Using nlohmann/json submodule from: ${CINDER_NLOHMANN_DIR}" )
else()
    # Fallback to bundled nlohmann/json
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_INC_DIR}/nlohmann )
    ci_log_v( "Using bundled nlohmann/json" )
endif()

# Configure GLM submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/glm" )
    set( CINDER_GLM_DIR "${CINDER_SUBMODULES_DIR}/glm" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_GLM_DIR} )
    ci_log_v( "Using GLM submodule from: ${CINDER_GLM_DIR}" )
else()
    # Fallback to bundled GLM
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_INC_DIR}/glm )
    ci_log_v( "Using bundled GLM" )
endif()

# Configure zlib submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/zlib" )
    set( CINDER_ZLIB_DIR "${CINDER_SUBMODULES_DIR}/zlib" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_ZLIB_DIR} )
    ci_log_v( "Using zlib submodule from: ${CINDER_ZLIB_DIR}" )
else()
    # Fallback to bundled zlib
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_SRC_DIR}/zlib )
    ci_log_v( "Using bundled zlib" )
endif()

# Configure FreeType submodule
if( EXISTS "${CINDER_SUBMODULES_DIR}/freetype" )
    set( CINDER_FREETYPE_DIR "${CINDER_SUBMODULES_DIR}/freetype" )
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_FREETYPE_DIR}/include )
    ci_log_v( "Using FreeType submodule from: ${CINDER_FREETYPE_DIR}" )
else()
    # Fallback to bundled FreeType
    list( APPEND CINDER_INCLUDE_SYSTEM_PRIVATE ${CINDER_INC_DIR}/freetype )
    ci_log_v( "Using bundled FreeType" )
endif() 