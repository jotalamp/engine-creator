#include "../engine-creator/EditableLine.h"
#include "gmock/gmock.h"
#include <bits/stdc++.h>

using namespace testing;
using ::testing::Eq;

class BaseEditableTest : public Test
{
protected:
    const unsigned int lineNumber = 123;
    const std::string name = "TestName";
    const std::string editableText = "EditableText";
};

class AnEditableLine : public BaseEditableTest
{
protected:
    EditableLine editableLine{lineNumber, name, editableText};
};

TEST_F(AnEditableLine, GetsCorrectLineNumber)
{
    ASSERT_THAT(editableLine.getLineNumber(), Eq(lineNumber));
}

TEST_F(AnEditableLine, GetsCorrectName)
{
    ASSERT_THAT(editableLine.getName(), Eq(name));
}

TEST_F(AnEditableLine, GetsCorrectEditableText)
{
    ASSERT_THAT(editableLine.getEditableText(), Eq(editableText));
}

TEST_F(AnEditableLine, GetsEditableTextAsEditedTextWhenCreated)
{
    ASSERT_THAT(*editableLine.getEditedText(), Eq(editableText));
}

TEST_F(AnEditableLine, IsEqualWithSimilarEditableLine)
{
    EditableLine editableLine1(lineNumber, name, editableText);
    EditableLine editableLine2(lineNumber, name, editableText);

    ASSERT_THAT(editableLine, Eq(editableLine));
}

TEST_F(AnEditableLine, IsNotEqualWithDifferentEditableLine)
{
    EditableLine editableLine1(lineNumber, name, editableText);
    EditableLine editableLine2(lineNumber, name, "SomeOtherEditableText");

    ASSERT_THAT(editableLine1, Ne(editableLine2));
}

class AnEditableFloatValue : public BaseEditableTest
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

TEST_F(AnEditableFloatValue, IsNotEqualWithDifferentEditableFloatValue)
{
    float float1 = 1;
    float float2 = 2;
    EditableFloatValue editableFloatValue1(lineNumber, name, editableText, float1);
    EditableFloatValue editableFloatValue2(lineNumber, name, editableText, float2);

    ASSERT_THAT(editableFloatValue1, Ne(editableFloatValue2));
}

class AnEditableIntegerValue : public BaseEditableTest
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

TEST_F(AnEditableIntegerValue, IsNotEqualWithDifferentEditableIntegerValue)
{
    int int1 = 1;
    int int2 = 2;
    EditableIntegerValue editableIntegerValue1(lineNumber, name, editableText, int1);
    EditableIntegerValue editableIntegerValue2(lineNumber, name, editableText, int2);

    ASSERT_THAT(editableIntegerValue1, Ne(editableIntegerValue2));
}