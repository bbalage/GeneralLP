#ifndef GENERALLP_TABLE_TABLE_HPP
#define GENERALLP_TABLE_TABLE_HPP

#include <memory>
#include <vector>
#include <map>
#include <string>

// Variable type for the row or column marker.
enum struct VarType
{
    X,
    V,
    U,
    US
};

struct VarPos
{
    size_t index;
    bool hor;
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
          std::initializer_list<VarType> varTypesHor,
          std::initializer_list<VarType> varTypesVer) : m_rows(rows),
                                                        m_cols(cols)
    {
        std::vector<T> v(cols, 0.0);
        m_table.resize(rows, v);
        loadVarNames(varTypesHor, true);
        loadVarNames(varTypesVer, false);
    }

    Table(size_t rows,
          size_t cols,
          std::initializer_list<VarType> varTypesHor,
          std::initializer_list<VarType> varTypesVer,
          std::initializer_list<T> vals) : Table(rows, cols, varTypesHor, varTypesVer)
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

    std::vector<size_t> varsOfType(VarType type, bool hor) const
    {
        std::vector<size_t> indices;
        const auto &vars = hor ? m_varNamesHor : m_varNamesVer;
        for (size_t i = 0; i < vars.size(); ++i)
        {
            if (vars[i].type == type)
                indices.push_back(i);
        }
        return indices;
    }

    std::vector<size_t> varsOfTypeHor(VarType type) const
    {
        return varsOfType(type, true);
    }

    std::vector<size_t> varsOfTypeVer(VarType type) const
    {
        return varsOfType(type, false);
    }

    std::vector<VarName> &varNamesHor() { return m_varNamesHor; }
    const std::vector<VarName> &varNamesHor() const { return m_varNamesHor; }
    std::vector<VarName> &varNamesVer() { return m_varNamesVer; }
    const std::vector<VarName> &varNamesVer() const { return m_varNamesVer; }

    VarType varTypeAtRow(size_t i) const { return m_varNamesVer[i].type; }
    VarType varTypeAtCol(size_t i) const { return m_varNamesHor[i].type; }

    std::vector<VarPos> &xsHor() { return varsOfTypeHor(VarType::X); }
    std::vector<VarPos> &vsHor() { return varsOfTypeHor(VarType::V); }
    std::vector<VarPos> &usHor() { return varsOfTypeHor(VarType::U); }
    std::vector<VarPos> &ussHor() { return varsOfTypeHor(VarType::US); }
    std::vector<VarPos> &xsVer() { return varsOfTypeVer(VarType::X); }
    std::vector<VarPos> &vsVer() { return varsOfTypeVer(VarType::V); }
    std::vector<VarPos> &usVer() { return varsOfTypeVer(VarType::U); }
    std::vector<VarPos> &ussVer() { return varsOfTypeVer(VarType::US); }
    const std::vector<VarPos> &xsHor() const { return varsOfTypeHor(VarType::X); }
    const std::vector<VarPos> &vsHor() const { return varsOfTypeHor(VarType::V); }
    const std::vector<VarPos> &usHor() const { return varsOfTypeHor(VarType::U); }
    const std::vector<VarPos> &ussHor() const { return varsOfTypeHor(VarType::US); }
    const std::vector<VarPos> &xsVer() const { return varsOfTypeVer(VarType::X); }
    const std::vector<VarPos> &vsVer() const { return varsOfTypeVer(VarType::V); }
    const std::vector<VarPos> &usVer() const { return varsOfTypeVer(VarType::U); }
    const std::vector<VarPos> &ussVer() const { return varsOfTypeVer(VarType::US); }

    bool operator==(const Table<T> &table) const
    {
        if (table.cols() != m_cols || table.rows() != m_rows)
            return false;
        if (table.varNamesVer().size() != m_varNamesVer.size() || table.varNamesHor().size() != m_varNamesHor.size())
            return false;
        for (size_t i = 0; i < m_varNamesHor.size(); ++i)
        {
            if (table.varNamesHor().at(i) != m_varNamesHor.at(i))
                return false;
        }
        for (size_t i = 0; i < m_varNamesVer.size(); ++i)
        {
            if (table.varNamesVer().at(i) != m_varNamesVer.at(i))
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
        if (row >= m_varNamesHor.size() || col >= m_varNamesVer.size())
            throw std::invalid_argument("Cannot switch given variable names.");
        auto varNameTmp = m_varNamesHor[col];
        m_varNamesHor[col] = m_varNamesVer[row];
        m_varNamesVer[row] = varNameTmp;
    }

private:
    size_t m_rows;
    size_t m_cols;
    std::vector<std::vector<T>> m_table;
    std::vector<VarName> m_varNamesHor;
    std::vector<VarName> m_varNamesVer;

    void loadVarNames(std::initializer_list<VarType> types, bool hor)
    {
        std::map<VarType, uint> counts = {
            {VarType::X, 0},
            {VarType::V, 0},
            {VarType::U, 0},
            {VarType::US, 0}};
        auto &varNames = hor ? m_varNamesHor : m_varNamesVer;
        for (auto type : types)
        {
            varNames.push_back(VarName{counts.at(type)++, type});
        }
    }
};

#endif