#ifndef GENERALLP_TABLE_TABLE_HPP
#define GENERALLP_TABLE_TABLE_HPP

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "../util/exception.hpp"

// Variable type for the row or column marker.
enum struct VarType
{
    X,
    V,
    U,
    US,
    OTHER
};

struct VarPos
{
    size_t index;
    bool isCol;
};

struct VarName
{
    size_t num;
    VarType type;

    bool operator==(const VarName &varName) const
    {
        return num == varName.num && type == varName.type;
    }

    const std::map<VarType, std::string> &varTypeStr() const
    {
        static const std::map<VarType, std::string> s_varTypeStr{
            {VarType::X, std::string("x")},
            {VarType::V, std::string("v")},
            {VarType::U, std::string("u")},
            {VarType::US, std::string("u*")}};
        return s_varTypeStr;
    }

    std::string string() const { return varTypeStr().at(type) + std::to_string(num + 1); }
};

template <class T>
class Table
{
public:
    Table(size_t rows,
          size_t cols,
          std::vector<VarName> varNamesCol,
          std::vector<VarName> varNamesRow,
          std::vector<std::vector<T>> tableValues) : m_rows{rows},
                                                     m_cols{cols},
                                                     m_varNamesCol{varNamesCol},
                                                     m_varNamesRow{varNamesRow},
                                                     m_table{tableValues}
    {
    }

    Table(size_t rows,
          size_t cols,
          std::initializer_list<VarName> varNamesCol,
          std::initializer_list<VarName> varNamesRow) : m_rows{rows}, m_cols{cols}, m_varNamesCol{varNamesCol}, m_varNamesRow{varNamesRow}
    {
        static_assert(std::is_floating_point_v<T>);
        // TODO: std::is_same_v<T, Fraction>
        static_assert(std::is_move_assignable_v<T>);
        std::vector<T> v(cols, 0.0);
        m_table.resize(rows, v);
    }

    Table(size_t rows,
          size_t cols,
          std::initializer_list<VarName> varNamesCol,
          std::initializer_list<VarName> varNamesRow,
          std::initializer_list<T> vals) : Table(rows, cols, varNamesCol, varNamesRow)
    {
        auto iter = vals.begin();
        for (size_t row = 0; row < m_rows; ++row)
        {
            for (size_t col = 0; col < m_cols; ++col)
            {
                if (iter == vals.end())
                    return;
                m_table[row][col] = *iter;
                ++iter;
            }
        }
    }

    Table(const Table &) = default;
    Table &operator=(const Table &) = default;
    Table(Table &&) = default;
    Table &operator=(Table &&) = default;

    T &at(size_t row, size_t col) { return m_table[row][col]; }
    const T &at(size_t row, size_t col) const { return m_table[row][col]; }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    std::vector<size_t> varsOfType(VarType type, bool isCol) const
    {
        std::vector<size_t> indices;
        const auto &vars = isCol ? m_varNamesCol : m_varNamesRow;
        for (size_t i = 0; i < vars.size(); ++i)
        {
            if (vars[i].type == type)
                indices.push_back(i);
        }
        return indices;
    }

    std::vector<size_t> varsOfTypeCol(VarType type) const
    {
        return varsOfType(type, true);
    }

    std::vector<size_t> varsOfTypeRow(VarType type) const
    {
        return varsOfType(type, false);
    }

    std::vector<VarName> &varNamesCol() { return m_varNamesCol; }
    const std::vector<VarName> &varNamesCol() const { return m_varNamesCol; }
    std::vector<VarName> &varNamesRow() { return m_varNamesRow; }
    const std::vector<VarName> &varNamesRow() const { return m_varNamesRow; }

    VarType varTypeAtRow(size_t i) const { return m_varNamesRow[i].type; }
    VarType varTypeAtCol(size_t i) const { return m_varNamesCol[i].type; }

    std::vector<VarPos> &xsCol() { return varsOfTypeCol(VarType::X); }
    std::vector<VarPos> &vsCol() { return varsOfTypeCol(VarType::V); }
    std::vector<VarPos> &usCol() { return varsOfTypeCol(VarType::U); }
    std::vector<VarPos> &ussCol() { return varsOfTypeCol(VarType::US); }
    std::vector<VarPos> &xsRow() { return varsOfTypeRow(VarType::X); }
    std::vector<VarPos> &vsRow() { return varsOfTypeRow(VarType::V); }
    std::vector<VarPos> &usRow() { return varsOfTypeRow(VarType::U); }
    std::vector<VarPos> &ussRow() { return varsOfTypeRow(VarType::US); }
    const std::vector<VarPos> &xsCol() const { return varsOfTypeCol(VarType::X); }
    const std::vector<VarPos> &vsCol() const { return varsOfTypeCol(VarType::V); }
    const std::vector<VarPos> &usCol() const { return varsOfTypeCol(VarType::U); }
    const std::vector<VarPos> &ussCol() const { return varsOfTypeCol(VarType::US); }
    const std::vector<VarPos> &xsRow() const { return varsOfTypeRow(VarType::X); }
    const std::vector<VarPos> &vsRow() const { return varsOfTypeRow(VarType::V); }
    const std::vector<VarPos> &usRow() const { return varsOfTypeRow(VarType::U); }
    const std::vector<VarPos> &ussRow() const { return varsOfTypeRow(VarType::US); }

    bool operator==(const Table<T> &table) const
    {
        if (table.cols() != m_cols || table.rows() != m_rows)
            return false;
        if (table.varNamesRow().size() != m_varNamesRow.size() || table.varNamesCol().size() != m_varNamesCol.size())
            return false;
        for (size_t i = 0; i < m_varNamesCol.size(); ++i)
        {
            if (table.varNamesCol().at(i) != m_varNamesCol.at(i))
                return false;
        }
        for (size_t i = 0; i < m_varNamesRow.size(); ++i)
        {
            if (table.varNamesRow().at(i) != m_varNamesRow.at(i))
                return false;
        }
        for (size_t row = 0; row < m_rows; ++row)
        {
            for (size_t col = 0; col < m_cols; ++col)
            {
                if (table.at(row, col) != m_table[row][col])
                    return false;
            }
        }
        return true;
    }

    size_t bColIndex() const { return m_cols - 1; }
    /**
     * Swaps horizontal variable name on col with vertical variable name on row.
     *
     * Throws std::invalid_argument if row and col exceed the number of stored
     * variable names on either axis.
     *
     * @param row
     * @param col
     */
    void swapVarNames(size_t row, size_t col)
    {
        if (row >= m_varNamesRow.size() || col >= m_varNamesCol.size())
            throw std::invalid_argument("Cannot switch given variable names.");
        auto varNameTmp = m_varNamesCol[col];
        m_varNamesCol[col] = m_varNamesRow[row];
        m_varNamesRow[row] = varNameTmp;
    }

    void removeRow(size_t in_row)
    {
        bool isInFirstStage = rows() - 2 == m_varNamesRow.size();
        if ((isInFirstStage && in_row == rows() - 2) || (!isInFirstStage && in_row == rows() - 1))
            throw LPException("Cannot remove z (value) row.");

        // 1. Resize table.
        for (size_t row = in_row; row < rows() - 1; ++row)
        {
            m_table[row] = std::move(m_table[row + 1]);
        }
        m_table.resize(rows() - 1);
        --m_rows;

        // 2. If it was the last row (z*), which was removed, then return without modifying variable names.
        if (isInFirstStage && in_row == rows())
            return;

        // 3. Resize var name list.
        for (size_t row = in_row; row < m_varNamesRow.size() - 1; ++row)
        {
            m_varNamesRow[row] = m_varNamesRow[row + 1];
        }
        m_varNamesRow.resize(m_varNamesRow.size() - 1);
    }

    void removeCol(size_t in_col)
    {
        if (in_col == cols() - 1)
            throw LPException("Cannot remove b (restriction) column.");

        // 1. Resize table.
        for (size_t row = 0; row < rows(); ++row)
        {
            for (size_t col = in_col; col < cols() - 1; ++col)
            {
                at(row, col) = std::move(at(row, col + 1));
            }
            m_table[row].resize(cols() - 1);
        }
        --m_cols;

        // 2. Resize var name list.
        for (size_t col = in_col; col < m_varNamesCol.size() - 1; ++col)
        {
            m_varNamesCol[col] = m_varNamesCol[col + 1];
        }
        m_varNamesCol.resize(m_varNamesCol.size() - 1);
    }

    constexpr T max_possible_value() const
    {
        static_assert(
            std::is_arithmetic_v<T>,
            "type is not arithmetic nor there is a specialization for the template type");
        return std::numeric_limits<T>::max();
    }

private:
    size_t m_rows;
    size_t m_cols;
    std::vector<VarName> m_varNamesCol;
    std::vector<VarName> m_varNamesRow;
    std::vector<std::vector<T>> m_table;
};

typedef Table<double> TableD;
typedef Table<float> TableF;

#endif