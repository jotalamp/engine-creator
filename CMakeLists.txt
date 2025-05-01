cmake_minimum_required(VERSION 3.10)
project(MinimalImGui)

set(CMAKE_CXX_STANDARD 17)


set(OpenGL_GL_PREFERENCE GLVND)

# 3rd party libraries
include(cmake/3rdparty.cmake)

# macro and configurations
include(cmake/config.cmake)

# projects
add_subdirectory(src)
