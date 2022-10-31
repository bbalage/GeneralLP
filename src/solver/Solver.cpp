#include "Solver.hpp"
#include <limits>
#include <iostream>
#include "../util/exception.hpp"
#include "../util/calc.hpp"

TableD Solver::calcNextStageOne(const TableD &table)
{
    auto [pivotRow, pivotCol] = findUSSPivotElement(table);
    TableD pivotedTable = glp::pivot(table, pivotRow, pivotCol);
    pivotedTable.swapVarNames(pivotRow, pivotCol);
    return pivotedTable;
}

std::pair<size_t, size_t> Solver::findUSSPivotElement(const TableD &table) const
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
    if (!pivotFound)
        throw LPException(std::string("No pivot element could be found."));
    return std::make_pair(pivotRow, pivotCol);
}
