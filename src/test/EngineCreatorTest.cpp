#include "../engine-creator/EngineCreator.h"
#include "gmock/gmock.h"
#include <bits/stdc++.h>

using namespace testing;
using ::testing::Eq;

class AnEngineCreator : public Test
{
public:
    EngineCreator engineCreator;

    void SetUp() override
    {
        engineCreator.setCreatedEngineFileName("test_engine");
    }
};

TEST_F(AnEngineCreator, FirstEditedLineIsSameAsInTemplateEngineWhenCreated)
{
    ASSERT_THAT(engineCreator.getEditedLine(0), Eq("import \"engine_sim.mr\""));
}

TEST_F(AnEngineCreator, EditedLine134IsSameAsInDefaultEngine)
{
    ASSERT_THAT(engineCreator.getEditedLine(134), Eq("        name: \"Audi 2.3 inline 5\","));
}

TEST_F(AnEngineCreator, ReplacesTextInLine)
{
    std::string newName = "NEW_NAME";
    std::string newLine = "        name: \"" + newName + "\",";
    engineCreator.replaceTextInLine(134, "Audi 2.3 inline 5", newName);
    ASSERT_THAT(engineCreator.getEditedLine(134), Eq(newLine));
}


TEST_F(AnEngineCreator, ThrowsWhenEditableTextNotFoundInOriginalLine)
{
    unsigned int lineNumber = 134;
    std::string name = "engine.name";
    std::string textThatNotFoundInOriginalLine = "?";
    ASSERT_THROW(engineCreator.addEditableValue(lineNumber, name, textThatNotFoundInOriginalLine), TextNotFoundFromTemplateFileException);
}

TEST_F(AnEngineCreator, ThrowsWhenEditableLineNotExist)
{
    std::string textThatNotExist = "????";
    ASSERT_THROW(engineCreator.getEditableLine(textThatNotExist), EditableLineNotExistException);
}

TEST_F(AnEngineCreator, DISABLED_GetsCorrectFloatValue)
{
    unsigned int lineNumber = 23;
    std::string name = "limiter_duration";
    float defaultFloatValue = 0.1f;
    engineCreator.addEditableValue(lineNumber, name, "0.1");
    ASSERT_THAT(*engineCreator.getEditableFloatValue(name)->getEditedFloatValue(),Eq(defaultFloatValue));
}
/*
TEST_F(EngineCreatorTest, GetsCorrectEditableIntegerValue)
{
    unsigned int lineNumber = 18;
    std::string name = "rev_limit";
    std::string editableText = "7500";
    engineCreator.addEditableIntegerValue(lineNumber, name, editableText);
    ASSERT_THAT(engineCreator.getEditableIntegerValue(name)->getEditableText(),Eq(editableText));
}
*/
TEST_F(AnEngineCreator, ThrowsWhenTextCanNotBeConvertedToNumber)
{
    unsigned int lineNumber = 18;
    std::string name = "rev_limit";
    std::string textThatNotCanBeConvertedToNumber = "?";
    ASSERT_ANY_THROW(EditableIntegerValue(lineNumber, name, textThatNotCanBeConvertedToNumber));
}
/*
TEST_F(EngineCreatorTest, GetsCorrectShortestStringRepresentationOfFloat)
{
    ASSERT_THAT(engineCreator.shortestStringRepresentation(0.001), Eq("0.001"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(-0.001), Eq("-0.001"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(-1), Eq("-1"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(1.0), Eq("1.0"));
}
*/
