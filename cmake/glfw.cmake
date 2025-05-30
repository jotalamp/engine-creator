option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES ON)
option(GLFW_BUILD_TESTS ON)
option(GLFW_INSTALL ON)
add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/glfw)

set_target_properties(glfw PROPERTIES FOLDER 3rdparty) # Override standard 'GLFW3' subfolder

set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/glfw/include)
set(GLFW_DEFINITIONS -DGLFW_INCLUDE_NONE)
set(GLFW_LIBRARIES ${GLFW_LIBRARIES} glfw)
