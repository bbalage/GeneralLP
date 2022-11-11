#include <iostream>

#include <memory>
#include <iostream>
#include "table/Table.hpp"
#include "printer/TablePrinter.hpp"
#include "solver/Solver.hpp"
#include "util/file.hpp"
#include "parser/TableParser.hpp"

int main()
{
    std::unique_ptr<TablePrinter<double>> tablePrinter(new TablePrinterTextStream<double>(std::cout));
    std::unique_ptr<Solver<double>> solver(new SolverSimple<double>);
    std::unique_ptr<TableParser<double>> tableParser(new TableParserText<double>);

    std::string filePath("/home/bbalage/ForUniversity/Bead/MSc-II/numanal/GeneralLP/resources/table1.txt");
    std::string descriptor = glp::fileContentAsString(filePath);
    // TODO: Write parser
    // Table<double> table = tableParser->parseTable(descriptor);

    // solver->solveGLPTask(table, *tablePrinter);
    std::cout << "Done.";
}