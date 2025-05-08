#include "../engine-creator/EditableLine.h"
#include "gmock/gmock.h"
#include <bits/stdc++.h>

using namespace testing;
using ::testing::Eq;

class EditableLineTest : public Test
{
public:

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }
};

TEST_F(EditableLineTest, GetCorrectLineNumber)
{
    unsigned int arbitaryLineNumber = 99;
    EditableLine editableLine(arbitaryLineNumber, "", "");
    ASSERT_THAT(editableLine.getLineNumber(), Eq(arbitaryLineNumber));
}

TEST_F(EditableLineTest, GetCorrectName)
{
    const std::string arbitaryName = "Name123";
    EditableLine editableLine(0, arbitaryName, "");
    ASSERT_THAT(editableLine.getName(), Eq(arbitaryName));
}

TEST_F(EditableLineTest, GetCorrectEditableText)
{
    const std::string editableText = "Audi 2.3 inline 5";
    EditableLine editableLine(0, "", editableText);
    ASSERT_THAT(editableLine.getEditableText(), Eq(editableText));
}

TEST_F(EditableLineTest, GetCorrectEditedText)
{
    const std::string editableText = "Audi 2.3 inline 5";
    EditableLine editableLine(0, "", editableText);
    ASSERT_THAT(*editableLine.getEditedText(), Eq(editableText));
}

TEST_F(EditableLineTest, SameLinesAreEqual)
{
    EditableLine editableLine(123, "engine.name", "Test Engine");
    ASSERT_THAT(editableLine, Eq(editableLine));
}

TEST_F(EditableLineTest, DifferentLinesAreNotEqual)
{
    EditableLine editableLine1(123, "engine.name", "Test Engine 1");
    EditableLine editableLine2(123, "engine.name", "Test Engine 2");
    ASSERT_THAT(editableLine1, Ne(editableLine2));
}