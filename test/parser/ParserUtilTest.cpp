#include <gtest/gtest.h>
#include <memory>

#include "../../src/parser/parser_util.hpp"

class ParserUtilTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

public:
    ParserUtilTest()
    {
    }
    ~ParserUtilTest()
    {
    }
};

TEST_F(ParserUtilTest, FirstMeaningFulCharNoNewline)
{
    const std::string text = "  \t  x1 blabla";
    constexpr size_t expectedIndex = 5;

    size_t actualIndex = glp::nextMeaningfulChar(text, 0);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, FirstMeaningFulCharWithNewline)
{
    const std::string text = "  \n\t  x1 blabla";
    constexpr size_t expectedIndex = 2;

    size_t actualIndex = glp::nextMeaningfulChar(text, 0);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, FirstMeaningFulCharNoMeaningful)
{
    const std::string text = " \t   ";
    constexpr size_t expectedIndex = std::string::npos;

    size_t actualIndex = glp::nextMeaningfulChar(text, 0);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, FirstMeaningFulCharEmptyString)
{
    const std::string text = "";
    constexpr size_t expectedIndex = std::string::npos;

    size_t actualIndex = glp::nextMeaningfulChar(text, 0);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, FirstMeaningFulCharNthStart)
{
    const std::string text = "   \t    k fsdv";
    constexpr size_t expectedIndex = 10;

    size_t actualIndex = glp::nextMeaningfulChar(text, 9);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, FirstMeaningFulCharIntoMeaningfulStartIndex)
{
    const std::string text = " xx www";
    constexpr size_t expectedIndex = 4;

    size_t actualIndex = glp::nextMeaningfulChar(text, 4);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, FirstMeaningFulCharOverIndexing)
{
    const std::string text = "   kdnf edkf";
    constexpr size_t expectedIndex = std::string::npos;

    size_t actualIndex = glp::nextMeaningfulChar(text, 13);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, FirstMeaningFulCharEmptyStringOverIndex)
{
    const std::string text = "";
    constexpr size_t expectedIndex = std::string::npos;

    size_t actualIndex = glp::nextMeaningfulChar(text, 7);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, NextSpaceNoNewline)
{
    const std::string text = "blabla   blfnv";
    constexpr size_t expectedIndex = 6;

    size_t actualIndex = glp::nextSpace(text, 0);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, NextSpaceWithNewline)
{
    const std::string text = "012345\n\t";
    constexpr size_t expectedIndex = 6;

    size_t actualIndex = glp::nextSpace(text, 0);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, NextSpaceNoSpace)
{
    const std::string text = "rrrrrrrrr";
    constexpr size_t expectedIndex = std::string::npos;

    size_t actualIndex = glp::nextSpace(text, 0);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, NextSpaceEmptyString)
{
    const std::string text = "";
    constexpr size_t expectedIndex = std::string::npos;

    size_t actualIndex = glp::nextSpace(text, 0);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, NextSpaceNthStart)
{
    const std::string text = "mmm   fff fsdv";
    constexpr size_t expectedIndex = 9;

    size_t actualIndex = glp::nextSpace(text, 6);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, NextSpaceIntoSpaceStartIndex)
{
    const std::string text = "xx    www";
    constexpr size_t expectedIndex = 3;

    size_t actualIndex = glp::nextSpace(text, 3);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, NextSpaceOverIndexing)
{
    const std::string text = "   kdnf edkf";
    constexpr size_t expectedIndex = std::string::npos;

    size_t actualIndex = glp::nextSpace(text, 13);

    ASSERT_EQ(expectedIndex, actualIndex);
}

TEST_F(ParserUtilTest, NextSpaceEmptyStringOverIndex)
{
    const std::string text = "";
    constexpr size_t expectedIndex = std::string::npos;

    size_t actualIndex = glp::nextSpace(text, 7);

    ASSERT_EQ(expectedIndex, actualIndex);
}