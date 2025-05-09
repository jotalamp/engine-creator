set(SOURCES 
    ../engine-creator/EngineCreator.cpp
    ../engine-creator/EditableValue.cpp
    EngineCreatorTest.cpp
    EditableValueTest.cpp
    mainTest.cpp)

make_executable()

target_link_libraries(test gmock)
target_link_libraries(test gtest)