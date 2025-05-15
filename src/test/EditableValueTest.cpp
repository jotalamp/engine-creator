#include "../engine-creator/EditableValue.h"
#include "gmock/gmock.h"

using namespace testing;
using ::testing::Eq;

class AnEditableValue : public Test
{
protected:
    const unsigned int lineNumber = 123;
    const std::string name = "TestName";
    const std::string editableText = "200";
    std::string originalLine = "        starter_torque: 200 * units.lb_ft,";
    std::string editedLine = "        starter_torque: 200 * units.lb_ft,";

    EditableValue editableValue{lineNumber, name, editableText, &originalLine, &editedLine};
};

TEST_F(AnEditableValue, GivesCorrectOriginalLine)
{
    ASSERT_THAT(editableValue.getOriginalLine(), Eq(originalLine));
}

TEST_F(AnEditableValue, CanSetOriginalLine)
{
    const std::string newOriginalLine = "        starter_torque: 234 * units.lb_ft,";
    editableValue.setEditedLine(newOriginalLine);

    ASSERT_THAT(editableValue.getEditedLine(), Eq(newOriginalLine));
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
    EditableValue editableValue1(lineNumber, name, editableText);
    EditableValue editableValue2(lineNumber, name, editableText);

    ASSERT_THAT(editableValue1, Eq(editableValue2));
}

TEST_F(AnEditableValue, IsNotEqualWithDifferentEditableValue)
{
    const std::string editableText1 = "Text1";
    const std::string editableText2 = "Text2";
    EditableValue editableValue1(lineNumber, name, editableText1);
    EditableValue editableValue2(lineNumber, name, editableText2);

    ASSERT_THAT(editableValue1, Ne(editableValue2));
}

TEST_F(AnEditableValue, GivesCorrectStartPartOfText)
{
    std::string originalLine = "        starter_torque: 200 * units.lb_ft,";

    EditableNumericValue editableNumericValue{lineNumber, name, "200", &originalLine, &editedLine};

    ASSERT_THAT(editableNumericValue.getTextStart(), Eq("        starter_torque: "));
}

class AnEditableStringValue : public AnEditableValue
{
protected:
    EditableStringValue editableStringValue{lineNumber, name, editableText};
};

TEST_F(AnEditableStringValue, GetsEditableTextAsEditedTextWhenCreated)
{
    ASSERT_THAT(*editableStringValue.getEditedLine(), Eq(editableText));
}

TEST_F(AnEditableStringValue, IsEqualWithSimilarEditableStringValue)
{
    EditableStringValue editableStringValue1(lineNumber, name, editableText);
    EditableStringValue editableStringValue2(lineNumber, name, editableText);

    ASSERT_THAT(editableStringValue1, Eq(editableStringValue2));
}

TEST_F(AnEditableStringValue, IsNotEqualWithDifferentEditableStringValue)
{
    EditableStringValue editableStringValue1(lineNumber, name, editableText);
    EditableStringValue editableStringValue2(lineNumber, name, "SomeOtherEditableText");

    ASSERT_THAT(editableStringValue1, Ne(editableStringValue2));
}

class AnEditableNumericValue : public AnEditableValue
{
protected:
    const std::string editableTextSimilarToFloat = "79.5";
    const float floatSimilarToEditableText = 79.5;
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    EditableNumericValue editableNumericValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};
};

TEST_F(AnEditableNumericValue, ThrowsWhenOriginalLineIsNullPointer)
{
    ASSERT_THROW(EditableNumericValue(lineNumber, name, editableText, nullptr), OriginalLineIsNullPointerException);
}

TEST_F(AnEditableNumericValue, GivesCorrectMiddlePartOfText)
{
    const std::string editableTextSimilarToFloat = "79.5";
    std::string originalLine = "    label stroke(79.5 * units.mm)";

    EditableNumericValue editableNumericValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    ASSERT_THAT(editableNumericValue.getTextMiddle(), Eq(" * "));
}

TEST_F(AnEditableNumericValue, CanSetUnitType)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableNumericValue editableNumericValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    const UnitType unitType = UnitType::Inch;
    editableNumericValue.setUnitType(unitType);
    ASSERT_THAT(editableNumericValue.getUnitTypeAsString(), Eq(editableNumericValue.unitTypes[unitType]));
}

class AnEditableFloatValue : public AnEditableNumericValue
{
protected:
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    const float floatSimilarToEditableText = 79.5;
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};
};

TEST_F(AnEditableFloatValue, GivesCorrectStartOfText)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    ASSERT_THAT(editableFloatValue.getTextStart(), Eq("    label stroke("));
}

TEST_F(AnEditableFloatValue, GivesCorrectEndOfText)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    ASSERT_THAT(editableFloatValue.getTextEnd(), Eq(")"));
}

TEST_F(AnEditableFloatValue, CanSetValue)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    float newValue = 1.23;
    const std::string newValueAsString = "1.23";

    editableFloatValue.setValue(newValue);

    std::string newOriginalLine = "    label stroke(1.230 * units.mm)";

    ASSERT_THAT(*editableFloatValue.getEditedFloatValue(), Eq(newValue));
    ASSERT_THAT(editableFloatValue.getEditedValueAsString(2), Eq(newValueAsString));
    //ASSERT_THAT(editableFloatValue.getEditableText(), Eq(newValueAsString));
    ASSERT_THAT(editableFloatValue.getEditedLine(), Eq(newOriginalLine));
}

TEST_F(AnEditableFloatValue, CanSetUnitType)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    const UnitType newUnitType = UnitType::Inch;

    editableFloatValue.setUnitType(newUnitType);

    std::string newOriginalLine = "    label stroke(79.5 * units.inch)";

    ASSERT_THAT(editableFloatValue.getEditedLine(), Eq(newOriginalLine));
    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(editableFloatValue.unitTypes[newUnitType]));
}

TEST_F(AnEditableFloatValue, CanSetValueAndUnitType)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    float newValue = 1.23;
    const std::string newValueAsString = "1.23";

    const UnitType newUnitType = UnitType::Inch;

    editableFloatValue.setValue(newValue);

    editableFloatValue.setUnitType(newUnitType);

    std::string newOriginalLine = "    label stroke(1.230 * units.inch)";

    ASSERT_THAT(*editableFloatValue.getEditedFloatValue(), Eq(newValue));
    ASSERT_THAT(editableFloatValue.getEditedValueAsString(2), Eq(newValueAsString));
    ASSERT_THAT(editableFloatValue.getEditedLine(), Eq(newOriginalLine));
    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(editableFloatValue.unitTypes[newUnitType]));
}

TEST_F(AnEditableFloatValue, CanDetectUnitType)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    const UnitType unitType = UnitType::mm;
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(editableFloatValue.unitTypes[unitType]));
}

TEST_F(AnEditableFloatValue, CanSplitTextToEditableTextUnitTypeAndRest)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    auto [textStart, editableText, textMiddle, unitAsString, textEnd] = editableFloatValue.split();

    ASSERT_THAT(textStart, Eq("    label stroke("));
    ASSERT_THAT(editableText, Eq("79.5"));
    ASSERT_THAT(textMiddle, Eq(" * "));
    ASSERT_THAT(unitAsString, Eq("units.mm"));
    ASSERT_THAT(textEnd, Eq(")"));
    ASSERT_THAT(textStart + editableText + textMiddle + unitAsString + textEnd, Eq(originalLine));
}

TEST_F(AnEditableFloatValue, CanSetValueAndKeepUnitType)
{
    std::string originalLine = "    label stroke(79.5 * units.mm)";
    std::string editedLine = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &originalLine, &editedLine};

    const UnitType newUnitType = UnitType::Inch;
    float newValue = 1.23;
    const std::string newValueAsString = "1.23";
    std::string newOriginalLine = "    label stroke(1.230 * units.inch)";

    editableFloatValue.setValue(newValue);
    editableFloatValue.setUnitType(newUnitType);
    editableFloatValue.setValue(newValue);

    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(editableFloatValue.unitTypes[newUnitType]));
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
    std::string originalLine = "    label stroke(A123.0 * units.mm)";
    const std::string stringThatCanNotBeConvertedToFloat = "A123.0";

    ASSERT_THROW(EditableFloatValue(lineNumber, name, stringThatCanNotBeConvertedToFloat, &originalLine, &editedLine), CanNotConvertStringToFloatException);
}

TEST_F(AnEditableFloatValue, IsNotEqualWithDifferentEditableFloatValue)
{
    std::string lineText1 = "    label stroke(1.00 * units.mm)";
    std::string editedText1 = "    label stroke(1.00 * units.mm)";
    std::string lineText2 = "    label stroke(1.01 * units.mm)";
    std::string editedText2 = "    label stroke(1.01 * units.mm)";
    const std::string editableText1 = "1.00";
    const std::string editableText2 = "1.01";
    EditableFloatValue editableFloatValue1(lineNumber, name, editableText1, &lineText1, &editedText1);
    EditableFloatValue editableFloatValue2(lineNumber, name, editableText2, &lineText2, &editedText2);

    ASSERT_THAT(editableFloatValue1, Ne(editableFloatValue2));
}

TEST_F(AnEditableFloatValue, IsEqualWithSimilarEditableFloatValue)
{
    std::string originalLine = "    label stroke(1.00 * units.mm)";
    std::string editedLine = "    label stroke(1.00 * units.mm)";
    const std::string editableText = "1.00";
    EditableFloatValue editableFloatValue1(lineNumber, name, editableText, &originalLine, &editedLine);
    EditableFloatValue editableFloatValue2(lineNumber, name, editableText, &originalLine, &editedLine);

    ASSERT_THAT(editableFloatValue1, Eq(editableFloatValue2));
}

TEST_F(AnEditableFloatValue, GivesUnitTypeNoneWhenAnyUnitTypeNotExistInLine)
{
    std::string originalLine = "            limiter_duration: 0.1";
    const unsigned int lineNumber = 23;
    const std::string name = "limiter_duration";
    const std::string editableText = "0.1";
    EditableFloatValue editableFloatValue(lineNumber, name, editableText, &originalLine, &editedLine);

    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), editableFloatValue.unitTypes[UnitType::None]);
    ASSERT_THAT(editableFloatValue.getUnitType(), UnitType::None);
}

TEST_F(AnEditableFloatValue, GivesCorrectUnitTypeWhenUnitTypeExistInLine)
{
    const unsigned int lineNumber = 18;
    const std::string name = "rev_limit";
    const std::string editableText = "7500";
    std::string originalLine = "    input rev_limit: 7500 * units.rpm;";
    EditableFloatValue editableFloatValue(lineNumber, name, editableText, &originalLine, &editedLine);
    editableFloatValue.setUnitType();
    ASSERT_THAT(editableFloatValue.getUnitType(), UnitType::Rpm);
}

class AnEditableIntegerValue : public AnEditableNumericValue
{
protected:
    std::string originalLine = "    input rev_limit: 7500 * units.rpm;";
    const std::string editableTextSimilarToInt = "7500";
    const int integerSimilarToEditableText = 7500;
    EditableIntegerValue editableIntegerValue{lineNumber, name, editableTextSimilarToInt, &originalLine, &editedLine};
};

TEST_F(AnEditableIntegerValue, ConvertsGivenStringToCorrespondingFloatValue)
{
    ASSERT_THAT(*editableIntegerValue.getEditedIntegerValue(), Eq(integerSimilarToEditableText));
}

TEST_F(AnEditableIntegerValue, ThrowsWhenStringCanNotBeConvertedToInt)
{
    std::string originalLine = "    input rev_limit: A123.0 * units.rpm;";
    const std::string stringThatCanNotBeConvertedToInt = "A123.0";

    ASSERT_THROW(EditableIntegerValue(lineNumber, name, stringThatCanNotBeConvertedToInt, &originalLine, &editedLine), CanNotConvertStringToIntException);
}

TEST_F(AnEditableIntegerValue, IsNotEqualWithDifferentEditableIntegerValue)
{
    std::string lineText1 = "    input rev_limit: 1 * units.rpm;";
    std::string lineText2 = "    input rev_limit: 2 * units.rpm;";
    const std::string editableText1 = "1";
    const std::string editableText2 = "2";
    EditableIntegerValue editableIntegerValue1(lineNumber, name, editableText1, &lineText1, &editedLine);
    EditableIntegerValue editableIntegerValue2(lineNumber, name, editableText2, &lineText2, &editedLine);

    ASSERT_THAT(editableIntegerValue1, Ne(editableIntegerValue2));
}

TEST_F(AnEditableIntegerValue, IsEqualWithSimilarEditableIntValue)
{
    std::string originalLine = "    input rev_limit: 1 * units.rpm;";
    const std::string editableText = "1";
    EditableIntegerValue editableIntValue1(lineNumber, name, editableText, &originalLine, &editedLine);
    EditableIntegerValue editableIntValue2(lineNumber, name, editableText, &originalLine, &editedLine);

    ASSERT_THAT(editableIntValue1, Eq(editableIntValue2));
}