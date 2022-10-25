#include <gtest/gtest.h>
#include <memory>

#include "../../src/solver/Solver.hpp"
#include "../../src/printer/TablePrinter.hpp"

class SolverTest : public ::testing::Test
{
protected:
    std::unique_ptr<TableD> p_table;

    void SetUp() override
    {
        p_table.reset(new TableD(5, 5));
        p_table->at(0, 0) = 1;
        p_table->at(0, 1) = 2;
        p_table->at(0, 2) = 1;
        p_table->at(0, 3) = 0;
        p_table->at(0, 4) = 50;
        p_table->at(1, 0) = 1;
        p_table->at(1, 1) = 1;
        p_table->at(1, 2) = 0;
        p_table->at(1, 3) = 0;
        p_table->at(1, 4) = 40;
        p_table->at(2, 0) = 1;
        p_table->at(2, 1) = 1;
        p_table->at(2, 2) = 2;
        p_table->at(2, 3) = -1;
        p_table->at(2, 4) = 20;
        p_table->at(3, 0) = 5;
        p_table->at(3, 1) = -2;
        p_table->at(3, 2) = 8;
        p_table->at(3, 3) = 0;
        p_table->at(3, 4) = 0;
        p_table->at(4, 0) = 2;
        p_table->at(4, 1) = 2;
        p_table->at(4, 2) = 2;
        p_table->at(4, 3) = -1;
        p_table->at(4, 4) = 60;
    }

    void TearDown() override
    {
    }

public:
    SolverTest()
    {
    }
    ~SolverTest()
    {
    }
};

TEST_F(SolverTest, DummyTest)
{
    Solver solver;
    TableD &table = *p_table;
    TablePrinter<double> printer;

    std::cout << "Before: " << std::endl;
    printer.printTable(table);
    solver.calcNextStageOne(table);
    std::cout << "After: " << std::endl;
    printer.printTable(table);

    ASSERT_EQ(1, 1);
}