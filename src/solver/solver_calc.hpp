#ifndef GENERALLP_SOLVER_SOLVERCALC_HPP
#define GENERALLP_SOLVER_SOLVERCALC_HPP

#include <limits>
#include <algorithm>

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
        size_t pivotRow = 0;
        size_t pivotCol = 0;
        bool pivotFound = false;
        for (size_t col = 0; col < table.bColIndex() && !pivotFound; ++col)
        {
            pivotFound = false;
            if (table.varTypeAtCol(col) == VarType::US)
                continue;
            if (table.at(table.rows() - 1, col) <= T(0))
                continue;
            T min = table.max_possible_value();
            for (size_t row = 0; row < table.varNamesRow().size(); ++row)
            {
                if (table.at(row, col) <= T(0))
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
            if (table.varTypeAtRow(pivotRow) != VarType::US)
                pivotFound = false;
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
        for (size_t col = 0; col < table.cols() - 1; ++col)
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

    /**
     * @brief Checks whether the primary optimum value is already found.
     *
     * @param table A table in the second stage.
     */
    template <class T>
    bool isPrimaryOptimumFound(const Table<T> &table)
    {
        for (size_t col = 0; col < table.cols() - 1; ++col)
        {
            if (table.at(table.rows() - 1, col) > T(0))
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Get the Primary Optimum object.
     *
     * @param table a table in the second stage
     */
    template <class T>
    T getPrimaryOptimum(const Table<T> &table)
    {
        return table.at(table.rows() - 1, table.cols() - 1);
    }

    /**
     * @brief Find pivot element in table.
     *
     * @param table a table in the second stage
     * @return std::pair where pair.first is the row of the pivot element and pair.second is the col.
     */
    template <class T>
    std::pair<size_t, size_t> findPivotElement_StageTwo(const Table<T> &table)
    {
        size_t pivotRow = 0;
        size_t pivotCol = 0;
        bool pivotFound = false;
        for (size_t col = 0; col < table.bColIndex() && !pivotFound; ++col)
        {
            if (table.at(table.rows() - 1, col) <= T(0))
                continue;
            T min = table.max_possible_value();
            for (size_t row = 0; row < table.varNamesRow().size(); ++row)
            {
                if (table.at(row, col) <= T(0))
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

    template <class T>
    Table<T> calcNext_StageTwo(const Table<T> &table)
    {
        auto [pivotRow, pivotCol] = findPivotElement_StageTwo(table);
        Table<T> pivotedTable = glp::pivot(table, pivotRow, pivotCol);
        pivotedTable.swapVarNames(pivotRow, pivotCol);
        return pivotedTable;
    }

    /**
     * Extracts the values of X and V variables and the resulting optimum (z) value from the table.
     *
     * @param table A table, which already has the primary optimum calculated and the values are accordingly set.
     * @return std::tuple which contains optimum data in the following order: x varnames and values, v varnames and values, optimum (z) value
     */
    template <class T>
    std::tuple<std::vector<VarNumAndVal<T>>, std::vector<VarNumAndVal<T>>, T> extractPrimaryOptimumData(const Table<T> &table)
    {
        auto sortedVariableValueExtractor = [&table](VarType type) -> std::vector<VarNumAndVal<T>>
        {
            const auto &indicesRow = table.varsOfTypeRow(type);
            std::vector<VarNumAndVal<T>> varNumsAndValues;
            varNumsAndValues.reserve(indicesRow.size());
            for (const auto &indexRow : indicesRow)
            {
                varNumsAndValues.push_back(VarNumAndVal<T>{
                    table.varNamesRow().at(indexRow).num,
                    table.at(indexRow, table.bColIndex())});
            }
            const auto &indicesCol = table.varsOfTypeCol(type);
            for (const auto &indexCol : indicesCol)
            {
                varNumsAndValues.push_back(VarNumAndVal<T>{
                    table.varNamesCol().at(indexCol).num, 0});
            }
            std::sort(
                varNumsAndValues.begin(),
                varNumsAndValues.end(),
                [](const VarNumAndVal<T> &a, const VarNumAndVal<T> &b)
                {
                    return a.num < b.num;
                });
            return varNumsAndValues;
        };
        return std::make_tuple(
            sortedVariableValueExtractor(VarType::X),
            sortedVariableValueExtractor(VarType::V),
            table.at(table.rows() - 1, table.cols() - 1) * -1);
    }
}
#endif