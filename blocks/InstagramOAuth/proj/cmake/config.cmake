# InstagramOAuth block configuration
# Set includes and libraries for the InstagramOAuth block

set(InstagramOAuth_INCLUDES "${CMAKE_CURRENT_LIST_DIR}/../../include" CACHE STRING "InstagramOAuth include path")

# The InstagramOAuth library is built as part of the block's CMakeLists.txt
# and linked automatically when the block is used 