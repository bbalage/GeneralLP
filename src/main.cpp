#include <iostream>

#include <memory>
#include <iostream>
#include "table/Table.hpp"
#include "printer/TablePrinter.hpp"
#include "solver/Solver.hpp"

int main()
{
    std::unique_ptr<TablePrinter<double>> tablePrinter(new TablePrinterTextStream<double>(std::cout));
    std::unique_ptr<Solver<double>> solver(new SolverSimple<double>);
    Table<double> table(5, 5,
                        {VarName{0, VarType::X}, VarName{1, VarType::X}, VarName{2, VarType::X}, VarName{2, VarType::V}},
                        {VarName{0, VarType::U}, VarName{1, VarType::US}, VarName{2, VarType::US}},
                        {1, 2, 1, 0, 50, 1, 1, 0, 0, 40, 1, 1, 2, -1, 20, 5, -2, 8, 0, 0, 2, 2, 2, -1, 60});
    solver->solveGLPTask(table, *tablePrinter);
    std::cout << "Done.";
}