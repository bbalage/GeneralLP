#include <iostream>

#include <memory>
#include <iostream>
#include "printer/TablePrinter.hpp"
#include "solver/Solver.hpp"
#include "util/file.hpp"
#include "table/TableCreator.hpp"

int main()
{
    std::unique_ptr<TablePrinter<double>> tablePrinter(new TablePrinterTextStream<double>(std::cout));
    std::unique_ptr<Solver<double>> solver(new SolverSimple<double>);
    std::unique_ptr<TableCreator<double>> tableCreator(new TableCreatorText<double>);

    std::string filePath("/home/bbalage/ForUniversity/Bead/MSc-II/numanal/GeneralLP/resources/table1.txt");
    std::string descriptor = glp::fileContentAsString(filePath);
    // TODO: Write parser
    // Table<double> table = tableCreator->createTable(descriptor);

    // solver->solveGLPTask(table, *tablePrinter);
    std::cout << "Done.";
}