#include "../engine-creator/EngineCreator.h"
#include "gmock/gmock.h"
#include <bits/stdc++.h>

using namespace testing;
using ::testing::Eq;

class EngineCreatorTest : public Test
{
public:
    EngineCreator engineCreator;

    void SetUp() override
    {
        engineCreator.setCreatedEngineFileName("test_engine");
    }
    void TearDown() override
    {
    }
};

TEST_F(EngineCreatorTest, FirstReadLineIsSameAsInDefaultEngine)
{
    ASSERT_THAT(engineCreator.getOriginalLine(0), Eq("import \"engine_sim.mr\""));
}

TEST_F(EngineCreatorTest, FirstLineWritedIsSameAsInDefaultEngine)
{
    engineCreator.writeAllLinesToFile();
    ASSERT_THAT(engineCreator.getLineFromCreatedFile(0), Eq("import \"engine_sim.mr\""));
}

TEST_F(EngineCreatorTest, Line134IsSameAsInDefaultEngine)
{
    ASSERT_THAT(engineCreator.getOriginalLine(134), Eq("        name: \"Audi 2.3 inline 5\","));
}

TEST_F(EngineCreatorTest, EngineNameIsCorrectAfterChanging)
{
    std::string newName = "NEW_NAME";
    std::string newLine = "        name: \"" + newName + "\",";
    engineCreator.changeLineTo(134, newLine);
    // ASSERT_THAT(engineCreator.getLine(134), Eq(newLine));
    engineCreator.writeAllLinesToFile();
    ASSERT_THAT(engineCreator.getLineFromCreatedFile(134), Eq(newLine));
}

TEST_F(EngineCreatorTest, TextExistsInOriginalLine)
{
    unsigned int lineNumberWhereTextToReplaceIs = 135;
    std::string textToReplace = "200";
    ASSERT_THAT(engineCreator.textExistsInOriginalLine(lineNumberWhereTextToReplaceIs, textToReplace), true);
}

TEST_F(EngineCreatorTest, TextIsCorrectAfterReplacingPartOfLine)
{
    unsigned int lineNumberWhereTextToReplaceIs = 135;
    std::string textToReplace = "200";
    std::string newText = "123";
    unsigned int lineLengthBeforeReplace = engineCreator.getOriginalLine(lineNumberWhereTextToReplaceIs).length();
    engineCreator.replaceTextInLine(lineNumberWhereTextToReplaceIs, textToReplace, newText);
    unsigned int lineLengthAfterReplace = engineCreator.getEditedLine(lineNumberWhereTextToReplaceIs).length();
    ASSERT_THAT(engineCreator.textExistsInEditedLine(lineNumberWhereTextToReplaceIs, newText), Eq(true));
    ASSERT_THAT(lineLengthAfterReplace, Eq(lineLengthBeforeReplace));
}

TEST_F(EngineCreatorTest, GetsCorrectChangeableText)
{
    unsigned int lineNumber = 134;
    std::string changeableText = "Audi 2.3 inline 5";
    ASSERT_THAT(engineCreator.getChangeableTextInLine(lineNumber), Eq(changeableText));
}