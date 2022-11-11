#ifndef GENERALLP_SOLVER_SOLVER_HPP
#define GENERALLP_SOLVER_SOLVER_HPP

#include "../table/Table.hpp"
#include "solver_calc.hpp"

template <class T>
class Solver
{
public:
    Solver() {}
    virtual ~Solver() {}
    Solver(const Solver &) = delete;
    Solver &operator=(const Solver &) = delete;
    Solver(Solver &&) = default;
    Solver &operator=(Solver &&) = default;

    virtual void solveGLPTask(const Table<T> &table, TablePrinter<T> &tablePrinter) = 0;
};

template <class T>
class SolverSimple : public Solver<T>
{
public:
    SolverSimple() {}

    void solveGLPTask(const Table<T> &in_table, TablePrinter<T> &tablePrinter) override
    {
        // 1. Solve stage one
        Table<T> table = in_table;
        while (!glp::isSecondaryOptimumFound(table))
        {
            tablePrinter.printTable(table);
            table = glp::calcNext_StageOne(table);
        }
        tablePrinter.printTable(table);
        if (glp::getSecondaryOptimum(table) != T(0))
        {
            tablePrinter.printNoSecondaryOptimum();
        }

        // 2. Remove unnecessary data from table.
        table = glp::firstStageTableToSecondStageTable(table);
        tablePrinter.printFirstToSecondStageTransfer();
        tablePrinter.printTable(table);
    }
};

#endif