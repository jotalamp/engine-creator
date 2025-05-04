set(SOURCES 
    ../engine-creator/EngineCreator.cpp
    mainTest.cpp
    EngineCreatorTest.cpp)

make_executable()

target_link_libraries(test gmock)
target_link_libraries(test gtest)