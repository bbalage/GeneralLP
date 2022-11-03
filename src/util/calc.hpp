#ifndef GENERALLP_UTIL_CALC_HPP
#define GENERALLP_UTIL_CALC_HPP

#include <type_traits>
#include "../table/Table.hpp"

namespace glp
{
    template <typename T>
    Table<T> pivot(const Table<T> &table, size_t pivotRow, size_t pivotCol)
    {
        static_assert(std::is_arithmetic<T>::value);
        if (pivotRow >= table.rows() || pivotCol >= table.cols())
            throw std::invalid_argument("Pivot element is not in table. Invalid pivotRow or pivotCol.");
        if (table.at(pivotRow, pivotCol) == 0)
            throw std::invalid_argument("Pivot element cannot be zero!");

        Table<T> new_table = table;

        // 1. Set the pivot element to 1 / pivot element.
        T pivotElement = table.at(pivotRow, pivotCol);
        new_table.at(pivotRow, pivotCol) = 1 / pivotElement;

        // 2. Divide the pivot element's row by pivot element.
        for (size_t col = 0; col < new_table.cols(); ++col)
        {
            if (col == pivotCol)
                continue;
            new_table.at(pivotRow, col) /= pivotElement;
        }

        // 3. Divide the pivot element's column by -(pivot element).
        for (size_t row = 0; row < new_table.rows(); ++row)
        {
            if (row == pivotRow)
                continue;
            new_table.at(row, pivotCol) /= -pivotElement;
        }

        // 4. Calculate the rest of the elements based on the rectangle rule.
        for (size_t row = 0; row < new_table.rows(); ++row)
        {
            for (size_t col = 0; col < new_table.cols(); ++col)
            {
                if (row == pivotRow || col == pivotCol)
                    continue;
                new_table.at(row, col) -= table.at(row, pivotCol) * table.at(pivotRow, col) / pivotElement;
            }
        }

        return new_table;
    }

}

#endif