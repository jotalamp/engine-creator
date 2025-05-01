#include "EngineCreator.h"
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
    ASSERT_THAT(engineCreator.getLine(0), Eq("import \"engine_sim.mr\""));
}

TEST_F(EngineCreatorTest, FirstLineWritedIsSameAsInDefaultEngine)
{
    engineCreator.writeAllLinesToFile();
    ASSERT_THAT(engineCreator.getLineFromCreatedFile(0), Eq("import \"engine_sim.mr\""));
}

TEST_F(EngineCreatorTest, Line134IsSameAsInDefaultEngine)
{
    ASSERT_THAT(engineCreator.getLine(134), Eq("        name: \"Audi 2.3 inline 5\","));
}

TEST_F(EngineCreatorTest, EngineNameIsCorrectAfterChanging)
{
    std::string newName = "NEW_NAME";
    std::string newLine = "        name: \"" + newName + "\",";
    engineCreator.changeLineTo(134, newLine);
    //ASSERT_THAT(engineCreator.getLine(134), Eq(newLine));
    engineCreator.writeAllLinesToFile();
    ASSERT_THAT(engineCreator.getLineFromCreatedFile(134), Eq(newLine));
}