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

    EditableValue editableValue{lineNumber, name, editableText};
};

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


class AnEditableFloatValue : public AnEditableValue
{
protected:
    const std::string editableTextSimilarToFloat = "0.02";
    const float floatSimilarToEditableText = 0.02;
    EditableFloatValue editableFloatValue{lineNumber, name, editableTextSimilarToFloat};
};

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


class AnEditableIntegerValue : public AnEditableValue
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