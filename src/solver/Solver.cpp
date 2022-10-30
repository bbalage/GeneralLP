#include "Solver.hpp"
#include <limits>
#include <iostream>

void Solver::calcNextStageOne(const TableD &table)
{
    // Find pivot element
    const auto &uss = table.varsOfTypeVer(VarType::US);
    size_t pivotRow = 0;
    size_t pivotCol = 0;
    bool pivotFound = false;
    for (size_t col = 0; col < table.bColIndex() && !pivotFound; ++col)
    {
        if (table.varTypeAtCol(col) == VarType::US)
            continue;
        double min = std::numeric_limits<double>::max();
        for (const auto &row : uss)
        {
            if (table.at(row, col) == 0.0)
            {
                continue;
            }
            double val = table.at(row, table.bColIndex()) / table.at(row, col);
            if (val < min)
            {
                min = val;
                pivotRow = row;
                pivotCol = col;
                pivotFound = true;
            }
        }
    }
    std::cout
        << "Pivot element is: ("
        << std::to_string(pivotRow)
        << ", "
        << std::to_string(pivotCol)
        << ")"
        << std::endl;
}