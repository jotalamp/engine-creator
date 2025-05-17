#include "../engine-creator/EditableValue.h"
#include "gmock/gmock.h"

using namespace testing;
using ::testing::Eq;

class AnEditableValue : public Test
{
public:
    static inline Unit::Units unitTypes;

protected:
    const unsigned int lineNumber = 123;
    const std::string name = "TestName";
    const std::string editableText = "200";
    std::string editedLine = "        starter_torque: 200 * units.lb_ft,";

    EditableValue editableValue{lineNumber, name, editableText, &editedLine};
};

TEST_F(AnEditableValue, TestUnits)
{
    for (const auto &unitType : unitTypes.getUnitToStringMap())
    {
        ASSERT_THAT(unitTypes[unitType.second], Eq(unitType.first));
        ASSERT_THAT(unitTypes[unitType.first], Eq(unitType.second));
    }

    bool allFound = true;
    std::string stringThatIsNotUnit;
    for (auto unitAsString : unitTypes.unitsAsStrings)
    {
        if (auto search = unitTypes.getStringToUnitMap().find(unitAsString); search != unitTypes.getStringToUnitMap().end())
        {
        }
        else
        {
            allFound = false;
            stringThatIsNotUnit = unitAsString;
            std::cout << "\n" << stringThatIsNotUnit << "\n";
        }
    }

    ASSERT_THAT(allFound, Eq(true));
}

TEST_F(AnEditableValue, GivesCorrectOriginalLine)
{
    ASSERT_THAT(editableValue.getOriginalLine(), Eq(editedLine));
}

TEST_F(AnEditableValue, GivesCorrectLineNumber)
{
    ASSERT_THAT(editableValue.getLineNumber(), Eq(lineNumber));
}

TEST_F(AnEditableValue, GivesCorrectName)
{
    ASSERT_THAT(editableValue.getName(), Eq(name));
}

TEST_F(AnEditableValue, GivesCorrectEditableText)
{
    ASSERT_THAT(editableValue.getEditableText(), Eq(editableText));
}

TEST_F(AnEditableValue, IsEqualWithSimilarEditableValue)
{
    EditableValue editableValue1(lineNumber, name, editableText, &editedLine);
    EditableValue editableValue2(lineNumber, name, editableText, &editedLine);

    ASSERT_THAT(editableValue1, Eq(editableValue2));
}

TEST_F(AnEditableValue, IsNotEqualWithDifferentEditableValue)
{
    std::string editedLine1 = "        starter_torque: 200 * units.lb_ft,";
    std::string editedLine2 = "        starter_torque: 201 * units.lb_ft,";
    const std::string editableText1 = "200";
    const std::string editableText2 = "201";
    EditableValue editableValue1(lineNumber, name, editableText1, &editedLine1);
    EditableValue editableValue2(lineNumber, name, editableText2, &editedLine2);

    ASSERT_THAT(editableValue1, Ne(editableValue2));
}

TEST_F(AnEditableValue, GivesCorrectStartPartOfText)
{
    EditableNumericValue editableNumericValue{lineNumber, name, "200", &editedLine};

    ASSERT_THAT(editableNumericValue.getTextStart(), Eq("        starter_torque: "));
}

class AnEditableStringValue : public AnEditableValue
{
protected:
    EditableStringValue editableStringValue{lineNumber, name, editableText, &editedLine};
};

TEST_F(AnEditableStringValue, GivesCorrectEditedValue)
{
    std::string editedLine = "        starter_torque: 200 * units.lb_ft,";
    std::string editableValue = "200";
    EditableStringValue editableStringValue(lineNumber, name, editableValue, &editedLine);

    ASSERT_THAT(*editableStringValue.getEditedValue(), Eq(editableValue));
}

TEST_F(AnEditableStringValue, IsEqualWithSimilarEditableStringValue)
{
    EditableStringValue editableStringValue1(lineNumber, name, editableText, &editedLine);
    EditableStringValue editableStringValue2(lineNumber, name, editableText, &editedLine);

    ASSERT_THAT(editableStringValue1, Eq(editableStringValue2));
}

TEST_F(AnEditableStringValue, IsNotEqualWithDifferentEditableStringValue)
{
    std::string editedLine1 = R"(        name: "Audi 2.3 inline 5",)";
    std::string editedLine2 = R"(        name: "Audi 2.3 inline 6",)";
    EditableStringValue editableStringValue1(lineNumber, name, "Audi 2.3 inline 5", &editedLine1);
    EditableStringValue editableStringValue2(lineNumber, name, "Audi 2.3 inline 6", &editedLine2);

    ASSERT_THAT(editableStringValue1, Ne(editableStringValue2));
}

class AnEditableNumericValue : public AnEditableValue
{
protected:
    const std::string editableTextSimilarToFloat = "79.5";
    const float floatSimilarToEditableText = 79.5;
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    EditableNumericValue editableNumericValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};
};

TEST_F(AnEditableNumericValue, GivesCorrectMiddlePartOfText)
{
    const std::string editableTextSimilarToFloat = "79.5";
    std::string originalLine = "    label stroke(79.5 * units.mm)";

    EditableNumericValue editableNumericValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableNumericValue.getTextMiddle(), Eq(" * "));
}

TEST_F(AnEditableNumericValue, CanSetUnitType)
{
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableNumericValue editableNumericValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    const UnitType unitType = UnitType::Inch;
    editableNumericValue.setUnitType(unitType);
    ASSERT_THAT(editableNumericValue.getUnitTypeAsString(), Eq(unitTypes[unitType]));
}

TEST_F(AnEditableNumericValue, DoesNotShowUnitWhenUnitTypeNoneIsSelected)
{
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableNumericValue editableNumericValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    const UnitType unitType = UnitType::None;
    editableNumericValue.setUnitType(unitType);

    std::string editedLineAfterUnitTypeChangedToNone = "    label stroke(79.5)";

    ASSERT_THAT(editableNumericValue.getEditedLine(), Eq(editedLineAfterUnitTypeChangedToNone));
}

class AnEditableFloatValue : public AnEditableNumericValue
{
protected:
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    const float floatSimilarToEditableText = 79.5;
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};
};

TEST_F(AnEditableFloatValue, GivesCorrectStartOfText)
{
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableFloatValue.getTextStart(), Eq("    label stroke("));
}

TEST_F(AnEditableFloatValue, GivesCorrectEndOfText)
{
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableFloatValue.getTextEnd(), Eq(")"));
}

TEST_F(AnEditableFloatValue, CanSetValue)
{
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine, 2};

    float newValue = 1.23;
    const std::string newValueAsString = "1.23";

    editableFloatValue.setValue(newValue);

    std::string newEditedLine = "    label stroke(1.23 * units.mm)";

    ASSERT_THAT(*editableFloatValue.getEditedFloatValue(), Eq(newValue));
    ASSERT_THAT(editableFloatValue.getEditedValueAsString(2), Eq(newValueAsString));
    ASSERT_THAT(editableFloatValue.getEditedLine(), Eq(newEditedLine));
}

TEST_F(AnEditableFloatValue, CanSetUnitType)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    const UnitType newUnitType = UnitType::Inch;

    editableFloatValue.setUnitType(newUnitType);

    std::string newEditedLine = "    label stroke(79.5 * units.inch)";

    ASSERT_THAT(editableFloatValue.getEditedLine(), Eq(newEditedLine));
    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(unitTypes[newUnitType]));
}

TEST_F(AnEditableFloatValue, DoesNotShowUnitWhenUnitTypeNoneIsSelectedAndValueIsChanged)
{
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine, 1};

    const UnitType unitType = UnitType::None;
    editableFloatValue.setUnitType(unitType);

    editableFloatValue.setValue(12.3);

    std::string editedLineAfterUnitTypeChangedToNone = "    label stroke(12.3)";

    ASSERT_THAT(editableFloatValue.getEditedLine(), Eq(editedLineAfterUnitTypeChangedToNone));
}

TEST_F(AnEditableFloatValue, CanSetValueAndUnitType)
{
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine, 2};

    float newValue = 1.23;
    const std::string newValueAsString = "1.23";

    const UnitType newUnitType = UnitType::Inch;

    editableFloatValue.setValue(newValue);

    editableFloatValue.setUnitType(newUnitType);

    std::string newOriginalLine = "    label stroke(1.23 * units.inch)";

    ASSERT_THAT(*editableFloatValue.getEditedFloatValue(), Eq(newValue));
    ASSERT_THAT(editableFloatValue.getEditedValueAsString(2), Eq(newValueAsString));
    ASSERT_THAT(editableFloatValue.getEditedLine(), Eq(newOriginalLine));
    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(unitTypes[newUnitType]));
}

TEST_F(AnEditableFloatValue, CanDetectUnitType)
{
    const UnitType unitType = UnitType::mm;
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(unitTypes[unitType]));
}

TEST_F(AnEditableFloatValue, TextStartIsCorrect)
{
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableFloatValue.getTextStart(), Eq("    label stroke("));
}

TEST_F(AnEditableFloatValue, EditableTextIsCorrect)
{
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableFloatValue.getEditableText(), Eq("79.5"));
}

TEST_F(AnEditableFloatValue, TextMiddleIsCorrect)
{
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableFloatValue.getTextMiddle(), Eq(" * "));
}

TEST_F(AnEditableFloatValue, UnitIsCorrect)
{
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq("units.mm"));
}

TEST_F(AnEditableFloatValue, TextEndIsCorrect)
{
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine};

    ASSERT_THAT(editableFloatValue.getTextEnd(), Eq(")"));
}

TEST_F(AnEditableFloatValue, CanSetValueAndKeepUnitType)
{
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &editedLine, 2};

    const UnitType newUnitType = UnitType::Inch;
    float newValue = 1.23;
    const std::string newValueAsString = "1.23";
    std::string newOriginalLine = "    label stroke(1.23 * units.inch)";

    editableFloatValue.setValue(newValue);
    editableFloatValue.setUnitType(newUnitType);
    editableFloatValue.setValue(newValue);

    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(unitTypes[newUnitType]));
    ASSERT_THAT(*editableFloatValue.getEditedFloatValue(), Eq(newValue));
    ASSERT_THAT(editableFloatValue.getEditedValueAsString(2), Eq(newValueAsString));
    ASSERT_THAT(editableFloatValue.getEditedLine(), Eq(newOriginalLine));
}

TEST_F(AnEditableFloatValue, ConvertsGivenStringToCorrespondingFloatValue)
{
    ASSERT_THAT(*editableFloatValue.getEditedFloatValue(), Eq(floatSimilarToEditableText));
}

TEST_F(AnEditableFloatValue, ThrowsWhenStringCanNotBeConvertedToFloat)
{
    std::string editedLine = "    label stroke(A123.0 * units.mm)";
    const std::string stringThatCanNotBeConvertedToFloat = "A123.0";

    ASSERT_THROW(EditableFloatValue(lineNumber, name, stringThatCanNotBeConvertedToFloat, &editedLine), CanNotConvertStringToFloatException);
}

TEST_F(AnEditableFloatValue, IsNotEqualWithDifferentEditableFloatValue)
{
    std::string originalLine1 = "    label stroke(1.00 * units.mm)";
    std::string editedText1 = "    label stroke(1.00 * units.mm)";
    std::string originalLine2 = "    label stroke(1.01 * units.mm)";
    std::string editedText2 = "    label stroke(1.01 * units.mm)";
    const std::string editableText1 = "1.00";
    const std::string editableText2 = "1.01";
    EditableFloatValue editableFloatValue1(lineNumber, name, editableText1, &editedText1);
    EditableFloatValue editableFloatValue2(lineNumber, name, editableText2, &editedText2);

    ASSERT_THAT(editableFloatValue1, Ne(editableFloatValue2));
}

TEST_F(AnEditableFloatValue, IsEqualWithSimilarEditableFloatValue)
{
    std::string originalLine = "    label stroke(1.00 * units.mm)";
    std::string editedLine = "    label stroke(1.00 * units.mm)";
    const std::string editableText = "1.00";
    EditableFloatValue editableFloatValue1(lineNumber, name, editableText, &editedLine);
    EditableFloatValue editableFloatValue2(lineNumber, name, editableText, &editedLine);

    ASSERT_THAT(editableFloatValue1, Eq(editableFloatValue2));
}

TEST_F(AnEditableFloatValue, GivesUnitTypeNoneWhenAnyUnitTypeNotExistInLine)
{
    std::string editedLine = "            limiter_duration: 0.1";
    const unsigned int lineNumber = 23;
    const std::string name = "limiter_duration";
    const std::string editableText = "0.1";
    EditableFloatValue editableFloatValue(lineNumber, name, editableText, &editedLine);

    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), unitTypes[UnitType::None]);
    ASSERT_THAT(editableFloatValue.getUnitType(), UnitType::None);
}

TEST_F(AnEditableFloatValue, GivesCorrectUnitTypeWhenUnitTypeExistInLine)
{
    const unsigned int lineNumber = 18;
    const std::string name = "rev_limit";
    const std::string editableText = "7500";
    std::string editedLine = "    input rev_limit: 7500 * units.rpm;";

    EditableFloatValue editableFloatValue(lineNumber, name, editableText, &editedLine);

    editableFloatValue.setUnitType();

    ASSERT_THAT(editableFloatValue.getUnitType(), UnitType::Rpm);
}

class AnEditableIntegerValue : public AnEditableNumericValue
{
protected:
    std::string originalLine = "    input rev_limit: 7500 * units.rpm;";
    std::string editedLine = "    input rev_limit: 7500 * units.rpm;";
    const std::string editableTextSimilarToInt = "7500";
    const int integerSimilarToEditableText = 7500;
    EditableIntegerValue editableIntegerValue{lineNumber, name, editableTextSimilarToInt, &editedLine};
};

TEST_F(AnEditableIntegerValue, ConvertsGivenStringToCorrespondingFloatValue)
{
    ASSERT_THAT(*editableIntegerValue.getEditedIntegerValue(), Eq(integerSimilarToEditableText));
}

TEST_F(AnEditableIntegerValue, ThrowsWhenStringCanNotBeConvertedToInt)
{
    std::string editedLine = "    input rev_limit: A123.0 * units.rpm;";
    const std::string stringThatCanNotBeConvertedToInt = "A123.0";

    ASSERT_THROW(EditableIntegerValue(lineNumber, name, stringThatCanNotBeConvertedToInt, &editedLine), CanNotConvertStringToIntException);
}

TEST_F(AnEditableIntegerValue, IsNotEqualWithDifferentEditableIntegerValue)
{
    std::string editedLine1 = "    input rev_limit: 1 * units.rpm;";
    std::string editedLine2 = "    input rev_limit: 2 * units.rpm;";
    const std::string editableText1 = "1";
    const std::string editableText2 = "2";
    EditableIntegerValue editableIntegerValue1(lineNumber, name, editableText1, &editedLine1);
    EditableIntegerValue editableIntegerValue2(lineNumber, name, editableText2, &editedLine2);

    ASSERT_THAT(editableIntegerValue1, Ne(editableIntegerValue2));
}

TEST_F(AnEditableIntegerValue, IsEqualWithSimilarEditableIntValue)
{
    std::string editedLine = "    input rev_limit: 1 * units.rpm;";
    const std::string editableText = "1";
    EditableIntegerValue editableIntValue1(lineNumber, name, editableText, &editedLine);
    EditableIntegerValue editableIntValue2(lineNumber, name, editableText, &editedLine);

    ASSERT_THAT(editableIntValue1, Eq(editableIntValue2));
}
