#include <gtest/gtest.h>
#include <memory>

#include "../../src/table/TableCreator.hpp"

class TableCreatorUtilTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

public:
    TableCreatorUtilTest()
    {
    }
    ~TableCreatorUtilTest()
    {
    }
};

TEST_F(TableCreatorUtilTest, ParseFirstTableFormated)
{
    const std::string descriptor = "    x1 x2 x3 v3 b\nu1  1  2  1  0  50\nu*2 1  1  0  0  40\nu*3 1  1  2  -1 20\n-z  5  -2 8  0  0\nz*  2  2  2  -1 60";
    TableCreatorText<double> tableCreatorText;
    Table<double> expectedTable(5, 5,
                                {VarName{0, VarType::X}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{2, VarType::V}},
                                {VarName{0, VarType::U}, VarName{1, VarType::US}, VarName{2, VarType::US}},
                                {1, 2, 1, 0, 50, 1, 1, 0, 0, 40, 1, 1, 2, -1, 20, 5, -2, 8, 0, 0, 2, 2, 2, -1, 60});

    Table<double> actualTable = tableCreatorText.createTable(descriptor);

    ASSERT_EQ(expectedTable, actualTable);
}

TEST_F(TableCreatorUtilTest, ParseFirstTableUnformated)
{
    const std::string descriptor = "x1 x2 x3 v3 b\nu1 1 2 1 0 50\nu*2 1 1 0 0 40\nu*3 1 1 2 -1 20\n-z 5 -2 8 0 0\nz* 2 2 2 -1 60";
    TableCreatorText<double> tableCreatorText;
    Table<double> expectedTable(5, 5,
                                {VarName{0, VarType::X}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{2, VarType::V}},
                                {VarName{0, VarType::U}, VarName{1, VarType::US}, VarName{2, VarType::US}},
                                {1, 2, 1, 0, 50, 1, 1, 0, 0, 40, 1, 1, 2, -1, 20, 5, -2, 8, 0, 0, 2, 2, 2, -1, 60});

    Table<double> actualTable = tableCreatorText.createTable(descriptor);

    ASSERT_EQ(expectedTable, actualTable);
}