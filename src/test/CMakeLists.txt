cmake_minimum_required(VERSION 3.10)
project(engine-creator-test)

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include ../engine-creator)
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild ../engine-creator)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(SOURCES
    mainTest.cpp
    ../engine-creator/EngineCreator.cpp
    EngineCreatorTest.cpp)

make_executable()

target_link_libraries(test pthread)
target_link_libraries(test gmock)
target_link_libraries(test gtest)
