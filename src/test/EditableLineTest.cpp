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
        //editableLine.setCreatedEngineFileName("test_engine");
    }
    void TearDown() override
    {
    }
};

TEST_F(EditableLineTest, GetCorrectLineNumber)
{
    unsigned int lineNumber = 99;
    EditableLine editableLine(lineNumber, "", "");
    ASSERT_THAT(editableLine.getLineNumber(), Eq(lineNumber));
}

TEST_F(EditableLineTest, GetCorrectName)
{
    const std::string name = "Name";
    EditableLine editableLine(0, name, "");
    ASSERT_THAT(editableLine.getName(), Eq(name));
}

TEST_F(EditableLineTest, GetCorrectEditableText)
{
    const std::string editableText = "Audi 2.3 inline 5";
    EditableLine editableLine(0, "", editableText);
    ASSERT_THAT(editableLine.getEditableText(), Eq(editableText));
}