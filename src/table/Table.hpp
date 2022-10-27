#ifndef GENERALLP_TABLE_TABLE_HPP
#define GENERALLP_TABLE_TABLE_HPP

#include <memory>
#include <vector>

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
        disperseVarTypes(varTypesHor, true);
        disperseVarTypes(varTypesVer, false);
    }
    Table(const Table &) = delete;
    Table &operator=(const Table &) = delete;
    Table(Table &&) = default;
    Table &operator=(Table &&) = default;

    T &at(size_t row, size_t col) { return m_table[row][col]; }
    const T &at(size_t row, size_t col) const { return m_table[row][col]; }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    std::vector<VarPos> &xs() { return m_xs; }
    std::vector<VarPos> &vs() { return m_vs; }
    std::vector<VarPos> &us() { return m_us; }
    std::vector<VarPos> &uss() { return m_uss; }
    const std::vector<VarPos> &xs() const { return m_xs; }
    const std::vector<VarPos> &vs() const { return m_vs; }
    const std::vector<VarPos> &us() const { return m_us; }
    const std::vector<VarPos> &uss() const { return m_uss; }

private:
    size_t m_rows;
    size_t m_cols;
    std::vector<std::vector<T>> m_table;
    // Normal variables marked by x index
    std::vector<VarPos> m_xs;
    // Utility variables marked by v index
    std::vector<VarPos> m_vs;
    // Utility variables marked by u index
    std::vector<VarPos> m_us;
    // Utility variables marked by u* index (us star)
    std::vector<VarPos> m_uss;

    void disperseVarTypes(std::initializer_list<VarType> types, bool hor)
    {
        size_t i = 0;
        for (auto type : types)
        {
            switch (type)
            {
            case VarType::X:
                m_xs.push_back(VarPos{i++, hor});
                break;
            case VarType::V:
                m_vs.push_back(VarPos{i++, hor});
                break;
            case VarType::U:
                m_us.push_back(VarPos{i++, hor});
                break;
            case VarType::US:
                m_uss.push_back(VarPos{i++, hor});
                break;
            }
        }
    }
};

#endif