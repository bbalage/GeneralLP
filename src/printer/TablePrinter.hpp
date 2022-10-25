#ifndef GENERALLP_PRINTER_TABLEPRINTER_HPP
#define GENERALLP_PRINTER_TABLEPRINTER_HPP

#include <iostream>
#include "../table/Table.hpp"

template <class T>
class TablePrinter
{
public:
    TablePrinter() {}
    ~TablePrinter() {}
    TablePrinter(const TablePrinter &) = delete;
    TablePrinter &operator=(const TablePrinter &) = delete;
    TablePrinter(TablePrinter &&) = default;
    TablePrinter &operator=(TablePrinter &&) = default;

    void printTable(const Table<T> &table)
    {
        for (size_t row = 0; row < table.rows(); ++row)
        {
            for (size_t col = 0; col < table.cols(); ++col)
            {
                std::cout << table.at(row, col) << " ";
            }
            std::cout << "\n";
        }
    }
};

#endif