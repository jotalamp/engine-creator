cmake_minimum_required(VERSION 3.10)
project(engine-creator)

set(CMAKE_CXX_STANDARD 23)

set(OpenGL_GL_PREFERENCE GLVND)

# 3rd party libraries
include(cmake/3rdparty.cmake)

# macro and configurations
include(cmake/config.cmake)

# projects
add_subdirectory(src)
