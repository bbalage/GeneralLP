#ifndef GENERALLP_TABLE_TABLE_HPP
#define GENERALLP_TABLE_TABLE_HPP

#include <memory>
#include <vector>

template <class T>
class Table
{
public:
    Table(size_t rows, size_t cols) : m_rows(rows),
                                      m_cols(cols)
    {
        std::vector<T> v(cols, 0.0);
        m_table.resize(rows, v);
    }
    Table(const Table &) = delete;
    Table &operator=(const Table &) = delete;
    Table(Table &&) = default;
    Table &operator=(Table &&) = default;

    T &at(size_t row, size_t col) { return m_table[row][col]; }
    const T &at(size_t row, size_t col) const { return m_table[row][col]; }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

private:
    size_t m_rows;
    size_t m_cols;
    std::vector<std::vector<T>> m_table;
};

#endif