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
        p_table.reset(new TableD(5, 5,
                                 {VarType::X, VarType::X, VarType::X, VarType::V},
                                 {VarType::U, VarType::US, VarType::US},
                                 {1, 2, 1, 0, 50, 1, 1, 0, 0, 40, 1, 1, 2, -1, 20, 5, -2, 8, 0, 0, 2, 2, 2, -1, 60}));
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
    TableD expectedTable(5, 5,
                         {VarType::X, VarType::X, VarType::X, VarType::V},
                         {VarType::U, VarType::US, VarType::US},
                         {-1, 1, -1, 1, 30, -1, 0, -2, 1, 20, 1, 1, 2, -1, 20, -5, -7, -2, 5, -100, -2, 0, -2, 1, 20});
    expectedTable.swapVarNames(2, 0);

    std::cout << "Before: " << std::endl;
    printer.printTable(table);
    auto actualTable = solver.calcNextStageOne(table);
    std::cout << "After: " << std::endl;
    printer.printTable(actualTable);

    ASSERT_EQ(expectedTable, actualTable);
}