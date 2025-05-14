#include "../engine-creator/EditableValue.h"
#include "gmock/gmock.h"
#include <bits/stdc++.h>

using namespace testing;
using ::testing::Eq;

class AnEditableValue : public Test
{
protected:
    const unsigned int lineNumber = 123;
    const std::string name = "TestName";
    const std::string editableText = "EditableText";
    std::string lineText = "        starter_torque: 200 * units.lb_ft,";
    std::string editedText = "        starter_torque: 200 * units.lb_ft,";

    EditableValue editableValue{lineNumber, name, editableText, &lineText, &editedText};
};

TEST_F(AnEditableValue, GivesCorrectLineText)
{
    ASSERT_THAT(editableValue.getOriginalText(), Eq(lineText));
}

TEST_F(AnEditableValue, CanSetLineText)
{
    const std::string newLineText = "        starter_torque: 234 * units.lb_ft,";
    editableValue.setLineText(newLineText);

    ASSERT_THAT(editableValue.getEditedText(), Eq(newLineText));
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

class AnEditableStringValue : public AnEditableValue
{
protected:
    EditableStringValue editableStringValue{lineNumber, name, editableText};
};

TEST_F(AnEditableStringValue, GetsEditableTextAsEditedTextWhenCreated)
{
    ASSERT_THAT(*editableStringValue.getEditedText(), Eq(editableText));
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
    const std::string editableTextSimilarToFloat = "0.02";
    const float floatSimilarToEditableText = 0.02;
    std::string lineText = "        starter_torque: 200 * units.lb_ft,";
    std::string editedText = "        starter_torque: 200 * units.lb_ft,";
    EditableNumericValue editableNumericValue{lineNumber, name, editableTextSimilarToFloat, &lineText, &editedText};
};

TEST_F(AnEditableNumericValue, ThrowsWhenLineTextIsNullPointer)
{
    EditableNumericValue editableNumericValueWithNullpointer{lineNumber, name, editableText, nullptr};
    
    ASSERT_THROW(editableNumericValueWithNullpointer.setUnitType(), OriginalTextIsNullPointerException);
}

TEST_F(AnEditableNumericValue, CanSetUnitType)
{
    const UnitType unitType = UnitType::Kg;
    editableNumericValue.setUnitType(unitType);
    ASSERT_THAT(editableNumericValue.getUnitTypeAsString(), Eq(editableNumericValue.unitTypes[unitType]));
}

class AnEditableFloatValue : public AnEditableNumericValue
{
protected:
    std::string lineText = "    label stroke(79.5 * units.mm)";
    std::string editedText = "    label stroke(79.5 * units.mm)";
    const std::string editableTextSimilarToFloat = "79.5";
    const float floatSimilarToEditableText = 79.5;
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat, &lineText, &editedText};
};

TEST_F(AnEditableFloatValue, CanSetValueAndUnitType)
{
    const UnitType unitType = UnitType::Inch;
    //editableFloatValue.setUnitType(unitType);

    float newValue = 1.23;
    const std::string newValueAsString = "1.23";
    editableFloatValue.setValue(newValue);
    editableFloatValue.setUnitType(unitType);

    //editableFloatValue.setValue(newValue);

    std::string newLineText = "    label stroke(1.23 * units.inch)";

    ASSERT_THAT(editableFloatValue.getUnitTypeAsString(), Eq(editableFloatValue.unitTypes[unitType]));
    ASSERT_THAT(*editableFloatValue.getEditedFloatValue(), Eq(newValue));
    ASSERT_THAT(editableFloatValue.getEditedValueAsString(2), Eq("1.23"));
    ASSERT_THAT(editableFloatValue.getEditableText(), Eq(newValueAsString));
    ASSERT_THAT(editableFloatValue.getEditedText(), Eq(newLineText));
}

TEST_F(AnEditableFloatValue, ConvertsGivenStringToCorrespondingFloatValue)
{
    ASSERT_THAT(*editableFloatValue.getEditedFloatValue(), Eq(floatSimilarToEditableText));
}

TEST_F(AnEditableFloatValue, ThrowsWhenStringCanNotBeConvertedToFloat)
{
    const std::string stringThatCanNotBeConvertedToFloat = "A123.0";

    ASSERT_THROW(EditableFloatValue(lineNumber, name, stringThatCanNotBeConvertedToFloat), CanNotConvertStringToFloatException);
}

TEST_F(AnEditableFloatValue, IsNotEqualWithDifferentEditableFloatValue)
{
    const std::string editableText1 = "1.00";
    const std::string editableText2 = "1.01";
    EditableFloatValue editableFloatValue1(lineNumber, name, editableText1);
    EditableFloatValue editableFloatValue2(lineNumber, name, editableText2);

    ASSERT_THAT(editableFloatValue1, Ne(editableFloatValue2));
}

TEST_F(AnEditableFloatValue, IsEqualWithSimilarEditableFloatValue)
{
    const std::string editableText = "1.00";
    EditableFloatValue editableFloatValue1(lineNumber, name, editableText);
    EditableFloatValue editableFloatValue2(lineNumber, name, editableText);

    ASSERT_THAT(editableFloatValue1, Eq(editableFloatValue2));
}

TEST_F(AnEditableFloatValue, GivesUnitTypeNoneWhenAnyUnitTypeNotExistInLine)
{
    const unsigned int lineNumber = 23;
    const std::string name = "limiter_duration";
    const std::string editableText = "0.1";
    EditableFloatValue editableFloatValue(lineNumber, name, editableText);

    ASSERT_THAT(editableFloatValue.getUnitType(), UnitType::None);
}

TEST_F(AnEditableFloatValue, GivesCorrectUnitTypeWhenUnitTypeExistInLine)
{
    const unsigned int lineNumber = 18;
    const std::string name = "rev_limit";
    const std::string editableText = "7500";
    std::string lineText = "    input rev_limit: 7500 * units.rpm;";
    EditableFloatValue editableFloatValue(lineNumber, name, editableText, &lineText);
    editableFloatValue.setUnitType();
    ASSERT_THAT(editableFloatValue.getUnitType(), UnitType::Rpm);
}

class AnEditableIntegerValue : public AnEditableNumericValue
{
protected:
    const std::string editableTextSimilarToInt = "123";
    const int integerSimilarToEditableText = 123;
    EditableIntegerValue editableIntegerValue{lineNumber, name, editableTextSimilarToInt};
};

TEST_F(AnEditableIntegerValue, ConvertsGivenStringToCorrespondingFloatValue)
{
    ASSERT_THAT(*editableIntegerValue.getEditedIntegerValue(), Eq(integerSimilarToEditableText));
}

TEST_F(AnEditableIntegerValue, ThrowsWhenStringCanNotBeConvertedToInt)
{
    const std::string stringThatCanNotBeConvertedToInt = "A123.0";

    ASSERT_THROW(EditableIntegerValue(lineNumber, name, stringThatCanNotBeConvertedToInt), CanNotConvertStringToIntException);
}

TEST_F(AnEditableIntegerValue, IsNotEqualWithDifferentEditableIntegerValue)
{
    const std::string editableText1 = "1";
    const std::string editableText2 = "2";
    EditableIntegerValue editableIntegerValue1(lineNumber, name, editableText1);
    EditableIntegerValue editableIntegerValue2(lineNumber, name, editableText2);

    ASSERT_THAT(editableIntegerValue1, Ne(editableIntegerValue2));
}

TEST_F(AnEditableIntegerValue, IsEqualWithSimilarEditableIntValue)
{
    const std::string editableText = "1";
    EditableIntegerValue editableIntValue1(lineNumber, name, editableText);
    EditableIntegerValue editableIntValue2(lineNumber, name, editableText);

    ASSERT_THAT(editableIntValue1, Eq(editableIntValue2));
}