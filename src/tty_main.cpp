#include <iostream>
#include <fstream>

#include <memory>
#include <iostream>
#include "printer/TablePrinter.hpp"
#include "solver/Solver.hpp"
#include "util/file.hpp"
#include "table/TableCreator.hpp"

int main(int argc, char **argv)
{
    std::cout << argc << std::endl;
    if (argc != 3)
    {
        std::cerr << "Program needs two input arguments, but " << argc - 1 << " is given." << std::endl;
        exit(1);
    }
    std::string inputFilePath(argv[1]);
    std::cout << "Using table in: " << inputFilePath << std::endl;
    std::string outputFilePath(argv[2]);
    std::cout << "Using " << outputFilePath << " as output file path." << std::endl;

    std::ofstream outputStream(outputFilePath);
    std::unique_ptr<TablePrinter<double>> tablePrinter(new TablePrinterTextStream<double>(outputStream));
    std::unique_ptr<Solver<double>> solver(new SolverSimple<double>);
    std::unique_ptr<TableCreator<double>> tableCreator(new TableCreatorText<double>);

    std::string descriptor = glp::fileContentAsString(inputFilePath);
    Table<double> table = tableCreator->createTable(descriptor);

    solver->solveGLPTask(table, *tablePrinter);

    outputStream.close();
}