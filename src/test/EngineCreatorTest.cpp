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

TEST_F(AnEngineCreator, ThrowsWhenEditableTextNotFoundInOriginalLineWhenAddingValue)
{
    const unsigned int lineNumber = 134;
    const std::string name = "engine.name";
    const std::string textThatNotExistInOriginalLine = "?";
    std::string lineText = "        starter_torque: 200 * units.lb_ft,";

    ASSERT_THROW(engineCreator.addEditableValue(lineNumber, name, textThatNotExistInOriginalLine), TextNotFoundException);
}

TEST_F(AnEngineCreator, ThrowsWhenEditableStringValueNotExistWhenGettingValue)
{
    const std::string stringValueThatNotExist = "?";

    ASSERT_THROW(engineCreator.getEditableStringValue(stringValueThatNotExist), EditableValueNotExistException);
}

TEST_F(AnEngineCreator, GivesEditableFloatValueAsEditedFloatValueWhenCreated)
{
    const unsigned int lineNumber = 23;
    const std::string name = "limiter_duration";
    const float editableFloatValue = 0.1f;
    std::string lineText = "        starter_torque: 200 * units.lb_ft,";
    engineCreator.addEditableValue(lineNumber, name, editableFloatValue);

    ASSERT_THAT(*engineCreator.getEditableFloatValue(name)->getEditedFloatValue(), Eq(editableFloatValue));
}

TEST_F(AnEngineCreator, GivesEditableIntValueAsEditedIntValueWhenCreated)
{
    const unsigned int lineNumber = 18;
    const std::string name = "rev_limit";
    const int editableIntValue = 7500;
    std::string lineText = "        starter_torque: 200 * units.lb_ft,";
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
    