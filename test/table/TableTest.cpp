#include <gtest/gtest.h>

#include "../../src/table/Table.hpp"

class TableTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

public:
    TableTest()
    {
    }
    ~TableTest()
    {
    }
};

TEST_F(TableTest, DummyTest)
{
    ASSERT_EQ(1, 1);
}