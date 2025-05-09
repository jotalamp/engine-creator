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

TEST_F(AnEngineCreator, EditedLineIsSameAsInTemplateEngineWhenCreated)
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

TEST_F(AnEngineCreator, ThrowsWhenEditableTextNotFoundInOriginalLineWhenAddingValue)
{
    const unsigned int lineNumber = 134;
    const std::string name = "engine.name";
    const std::string textThatNotExistInOriginalLine = "?";

    ASSERT_THROW(engineCreator.addEditableValue(lineNumber, name, textThatNotExistInOriginalLine), TextNotFoundFromTemplateFileException);
}

TEST_F(AnEngineCreator, ThrowsWhenEditableStringValueNotExistWhenGettingValue)
{
    const std::string stringValueThatNotExist = "?";

    ASSERT_THROW(engineCreator.getEditableStringValue(stringValueThatNotExist), EditableStringValueNotExistException);
}

TEST_F(AnEngineCreator, GivesEditableFloatValueAsEditedFloatValueWhenCreated)
{
    const unsigned int lineNumber = 23;
    const std::string name = "limiter_duration";
    const float editableFloatValue = 0.1f;
    engineCreator.addEditableValue(lineNumber, name, editableFloatValue);

    ASSERT_THAT(*engineCreator.getEditableFloatValue(name)->getEditedFloatValue(), Eq(editableFloatValue));
}

TEST_F(AnEngineCreator, GivesEditableIntValueAsEditedIntValueWhenCreated)
{
    const unsigned int lineNumber = 18;
    const std::string name = "rev_limit";
    const int editableIntValue = 7500;
    engineCreator.addEditableValue(lineNumber, name, editableIntValue);

    ASSERT_THAT(*engineCreator.getEditableIntegerValue(name)->getEditedIntegerValue(), Eq(editableIntValue));
}

TEST_F(AnEngineCreator, GivesShortestStringRepresentationOfFloat)
{
    ASSERT_THAT(engineCreator.shortestStringRepresentation(0.001), Eq("0.001"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(-0.001), Eq("-0.001"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(-1), Eq("-1"));
    ASSERT_THAT(engineCreator.shortestStringRepresentation(1.0), Eq("1.0"));
}
