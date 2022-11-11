#ifndef GENERALLP_SOLVER_SOLVERCALC_HPP
#define GENERALLP_SOLVER_SOLVERCALC_HPP

#include <limits>

#include "../table/Table.hpp"
#include "../util/exception.hpp"
#include "../util/calc.hpp"

namespace glp
{
    /**
     * @brief Find pivot element in table.
     *
     * @param table a table in the first stage
     * @return std::pair where pair.first is the row of the pivot element and pair.second is the col.
     */
    template <class T>
    std::pair<size_t, size_t> findPivotElement_StageOne(const Table<T> &table)
    {
        const auto &uss = table.varsOfTypeRow(VarType::US);
        size_t pivotRow = 0;
        size_t pivotCol = 0;
        bool pivotFound = false;
        for (size_t col = 0; col < table.bColIndex() && !pivotFound; ++col)
        {
            if (table.varTypeAtCol(col) == VarType::US)
                continue;
            if (table.at(table.rows() - 1, col) <= T(0))
                continue;
            T min = table.max_possible_value();
            for (const auto &row : uss)
            {
                if (table.at(row, col) == T(0))
                {
                    continue;
                }
                T val = table.at(row, table.bColIndex()) / table.at(row, col);
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

    /**
     * @brief Checks whether the optimum for the first stage is found.
     *
     * @param table a table in the first stage
     */
    template <class T>
    bool isSecondaryOptimumFound(const Table<T> &table)
    {
        for (size_t col = 0; col < table.cols(); ++col)
        {
            if (table.at(table.rows() - 1, col) > T(0))
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Get the Secondary Optimum object
     *
     * @param table a table in the first stage
     */
    template <class T>
    T getSecondaryOptimum(const Table<T> &table)
    {
        return table.at(table.rows() - 1, table.cols() - 1);
    }

    template <class T>
    Table<T> calcNext_StageOne(const Table<T> &table)
    {
        auto [pivotRow, pivotCol] = findPivotElement_StageOne(table);
        Table<T> pivotedTable = glp::pivot(table, pivotRow, pivotCol);
        pivotedTable.swapVarNames(pivotRow, pivotCol);
        return pivotedTable;
    }

    template <class T>
    Table<T> firstStageTableToSecondStageTable(const Table<T> &in_table)
    {
        Table<T> table = in_table;

        // 1. Remove the z* row
        table.removeRow(table.rows() - 1);

        // 2. Check if there is at least one u* row remained, and throw an exception if it has.
        const std::vector<size_t> &ussVarRows = table.varsOfTypeRow(VarType::US);
        if (ussVarRows.size() != 0)
            throw LPException(
                std::string("Some unexpected error occurred. Variable is u* at row ") + std::to_string(ussVarRows[0]));

        // 3. Remove u* cols.
        const std::vector<size_t> &ussVarCols = table.varsOfTypeCol(VarType::US);
        for (size_t i = 0; i < ussVarCols.size(); ++i)
        {
            table.removeCol(ussVarCols[i] - i);
        }

        return table;
    }
}
#endif