#include <gtest/gtest.h>
#include <memory>

#include "../../src/solver/solver_calc.hpp"
#include "../../src/printer/TablePrinter.hpp"

class SolverTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
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

TEST_F(SolverTest, FirstStepTest_Table1)
{
    TablePrinterTextStream<double> printer(std::cout); // TODO: Remove! Only debug code!
    TableD table(5, 5,
                 {VarName{0, VarType::X}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{2, VarType::V}},
                 {VarName{0, VarType::U}, VarName{1, VarType::US}, VarName{2, VarType::US}},
                 {1, 2, 1, 0, 50, 1, 1, 0, 0, 40, 1, 1, 2, -1, 20, 5, -2, 8, 0, 0, 2, 2, 2, -1, 60});
    TableD expectedTable(5, 5,
                         {VarName{2, VarType::US}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{2, VarType::V}},
                         {VarName{0, VarType::U}, VarName{1, VarType::US}, VarName{0, VarType::X}},
                         {-1, 1, -1, 1, 30, -1, 0, -2, 1, 20, 1, 1, 2, -1, 20, -5, -7, -2, 5, -100, -2, 0, -2, 1, 20});

    std::cout << "Before: " << std::endl; // TODO: Remove! Only debug code!
    printer.printTable(table);            // TODO: Remove! Only debug code!
    auto actualTable = glp::calcNext_StageOne(table);
    std::cout << "After: " << std::endl; // TODO: Remove! Only debug code!
    printer.printTable(actualTable);     // TODO: Remove! Only debug code!

    ASSERT_EQ(expectedTable, actualTable);
}

TEST_F(SolverTest, SecondStepTest_Table1)
{
    TablePrinterTextStream<double> printer(std::cout); // TODO: Remove! Only debug code!
    TableD table(5, 5,
                 {VarName{2, VarType::US}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{2, VarType::V}},
                 {VarName{0, VarType::U}, VarName{1, VarType::US}, VarName{0, VarType::X}},
                 {-1, 1, -1, 1, 30, -1, 0, -2, 1, 20, 1, 1, 2, -1, 20, -5, -7, -2, 5, -100, -2, 0, -2, 1, 20});
    TableD expectedTable(5, 5,
                         {VarName{2, VarType::US}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{1, VarType::US}},
                         {VarName{0, VarType::U}, VarName{2, VarType::V}, VarName{0, VarType::X}},
                         {0, 1, 1, -1, 10, -1, 0, -2, 1, 20, 0, 1, 0, 1, 40, 0, -7, 8, -5, -200, -1, 0, 0, -1, 0});

    std::cout << "Expected: " << std::endl; // TODO: Remove! Only debug code!
    printer.printTable(expectedTable);      // TODO: Remove! Only debug code!
    std::cout << "Before: " << std::endl;   // TODO: Remove! Only debug code!
    printer.printTable(table);              // TODO: Remove! Only debug code!
    auto actualTable = glp::calcNext_StageOne(table);
    std::cout << "After: " << std::endl; // TODO: Remove! Only debug code!
    printer.printTable(actualTable);     // TODO: Remove! Only debug code!

    ASSERT_EQ(expectedTable, actualTable);
}

TEST_F(SolverTest, FirstStepTest_Table2)
{
    TablePrinterTextStream<double> printer(std::cout); // TODO: Remove! Only debug code!
    TableD table(5, 4,
                 {VarName{0, VarType::X}, VarName{1, VarType::X}, VarName{0, VarType::V}},
                 {VarName{0, VarType::US}, VarName{1, VarType::U}, VarName{2, VarType::U}},
                 {7, 10, -1, 51, 1, 1, 0, 8, -1, 1, 0, 0, -15, -20, 0, 0, 7, 10, -1, 51});
    VarName expectedVarName_Row1{0, VarType::X};
    VarName expectedVarName_Col1{0, VarType::US};

    std::cout << "Before: " << std::endl; // TODO: Remove! Only debug code!
    printer.printTable(table);            // TODO: Remove! Only debug code!
    auto resultTable = glp::calcNext_StageOne(table);
    VarName actualVarName_Row1 = resultTable.varNamesRow()[0];
    VarName actualVarName_Col1 = resultTable.varNamesCol()[0];
    std::cout << "After: " << std::endl; // TODO: Remove! Only debug code!
    printer.printTable(resultTable);     // TODO: Remove! Only debug code!

    ASSERT_EQ(expectedVarName_Row1, actualVarName_Row1);
    ASSERT_EQ(expectedVarName_Col1, actualVarName_Col1);
}

TEST_F(SolverTest, FirstStepTest_Table1_Float)
{
    TablePrinterTextStream<float> printer(std::cout); // TODO: Remove! Only debug code!
    TableF table(5, 5,
                 {VarName{0, VarType::X}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{2, VarType::V}},
                 {VarName{0, VarType::U}, VarName{1, VarType::US}, VarName{2, VarType::US}},
                 {1, 2, 1, 0, 50, 1, 1, 0, 0, 40, 1, 1, 2, -1, 20, 5, -2, 8, 0, 0, 2, 2, 2, -1, 60});
    TableF expectedTable(5, 5,
                         {VarName{2, VarType::US}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{2, VarType::V}},
                         {VarName{0, VarType::U}, VarName{1, VarType::US}, VarName{0, VarType::X}},
                         {-1, 1, -1, 1, 30, -1, 0, -2, 1, 20, 1, 1, 2, -1, 20, -5, -7, -2, 5, -100, -2, 0, -2, 1, 20});

    std::cout << "Before: " << std::endl; // TODO: Remove! Only debug code!
    printer.printTable(table);            // TODO: Remove! Only debug code!
    auto actualTable = glp::calcNext_StageOne(table);
    std::cout << "After: " << std::endl; // TODO: Remove! Only debug code!
    printer.printTable(actualTable);     // TODO: Remove! Only debug code!

    ASSERT_EQ(expectedTable, actualTable);
}