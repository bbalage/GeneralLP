#ifndef GENERALLP_SOLVER_SOLVER_HPP
#define GENERALLP_SOLVER_SOLVER_HPP

#include "../table/Table.hpp"

typedef Table<double> TableD;

class Solver
{
public:
    Solver() {}
    ~Solver() {}
    Solver(const Solver &) = delete;
    Solver &operator=(const Solver &) = delete;
    Solver(Solver &&) = default;
    Solver &operator=(Solver &&) = default;

    void calcNextStageOne(TableD &table);
};

#endif