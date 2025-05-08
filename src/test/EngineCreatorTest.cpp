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
    const std::string newName = "NEW_NAME";
    const std::string newLine = "        name: \"" + newName + "\",";
    engineCreator.replaceTextInLine(134, "Audi 2.3 inline 5", newName);
    ASSERT_THAT(engineCreator.getEditedLine(134), Eq(newLine));
}


TEST_F(AnEngineCreator, ThrowsWhenEditableTextNotFoundInOriginalLine)
{
    const unsigned int lineNumber = 134;
    const std::string name = "engine.name";
    const std::string textThatNotFoundInOriginalLine = "?";
    ASSERT_THROW(engineCreator.addEditableValue(lineNumber, name, textThatNotFoundInOriginalLine), TextNotFoundFromTemplateFileException);
}

TEST_F(AnEngineCreator, ThrowsWhenEditableLineNotExist)
{
    const std::string textThatNotExist = "????";
    ASSERT_THROW(engineCreator.getEditableLine(textThatNotExist), EditableLineNotExistException);
}

TEST_F(AnEngineCreator, GivesCorrectEditedFloatValue)
{
    const unsigned int lineNumber = 23;
    const std::string name = "limiter_duration";
    const float defaultEditedFloatValue = 0.1f;
    engineCreator.addEditableValue(lineNumber, name, defaultEditedFloatValue);
    ASSERT_THAT(*engineCreator.getEditableFloatValue(name)->getEditedFloatValue(),Eq(defaultEditedFloatValue));
}

TEST_F(AnEngineCreator, GivesCorrectEditedIntegerValue)
{
    const unsigned int lineNumber = 18;
    const std::string name = "rev_limit";
    const int defaultEditedIntegerValue = 7500;
    engineCreator.addEditableValue(lineNumber, name, defaultEditedIntegerValue);
    ASSERT_THAT(*engineCreator.getEditableIntegerValue(name)->getEditedIntegerValue(),Eq(defaultEditedIntegerValue));
}

TEST_F(AnEngineCreator, ThrowsWhenTextCanNotBeConvertedToNumber)
{
    unsigned int lineNumber = 18;
    std::string name = "rev_limit";
    std::string textThatNotCanBeConvertedToNumber = "?";
    ASSERT_ANY_THROW(EditableIntegerValue(lineNumber, name, textThatNotCanBeConvertedToNumber));
}

TEST_F(AnEngineCreator, GetsCorrectShortestStringRepresentationOfFloat)
{
    ASSERT_THAT(engineCreator.shortestStringRepresentation(0.001), Eq("0.001"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(-0.001), Eq("-0.001"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(-1), Eq("-1"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(1.0), Eq("1.0"));
}

