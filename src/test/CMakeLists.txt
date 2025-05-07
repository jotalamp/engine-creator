set(SOURCES 
    ../engine-creator/EngineCreator.cpp
    ../engine-creator/EditableLine.cpp
    EngineCreatorTest.cpp
    EditableLineTest.cpp
    mainTest.cpp)

make_executable()

target_link_libraries(test gmock)
target_link_libraries(test gtest)