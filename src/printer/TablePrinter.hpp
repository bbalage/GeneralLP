#ifndef GENERALLP_PRINTER_TABLEPRINTER_HPP
#define GENERALLP_PRINTER_TABLEPRINTER_HPP

#include <ostream>
#include "../table/Table.hpp"

template <class T>
class TablePrinter
{
public:
    TablePrinter() {}
    virtual ~TablePrinter() {}
    TablePrinter(const TablePrinter &) = delete;
    TablePrinter &operator=(const TablePrinter &) = delete;
    TablePrinter(TablePrinter &&) = default;
    TablePrinter &operator=(TablePrinter &&) = default;

    virtual void printTable(const Table<T> &table) = 0;
    virtual void printNoSecondaryOptimum() = 0;
    virtual void printFirstToSecondStageTransfer() = 0;
    virtual void printPrimaryOptimumData(const std::vector<VarNumAndVal<T>> &xs,
                                         const std::vector<VarNumAndVal<T>> &vs,
                                         T optimum) = 0;
};

template <class T>
class TablePrinterTextStream : public TablePrinter<T>
{
public:
    TablePrinterTextStream(std::ostream &out_stream) : m_out_stream{out_stream} {}

    void printTable(const Table<T> &table) override
    {
        m_out_stream << "    ";
        for (const auto &name : table.varNamesCol())
        {
            m_out_stream << name.string() << " ";
        }
        m_out_stream << " b\n";
        const auto &varNamesVer = table.varNamesRow();
        for (size_t row = 0; row < table.rows(); ++row)
        {
            if (row < varNamesVer.size())
                m_out_stream << varNamesVer.at(row).string() << " ";
            else if (row == varNamesVer.size())
                m_out_stream << "-z ";
            else
                m_out_stream << "z* ";
            for (size_t col = 0; col < table.cols(); ++col)
            {
                m_out_stream << table.at(row, col) << " ";
            }
            m_out_stream << "\n";
        }
    }

    void printNoSecondaryOptimum() override
    {
        m_out_stream << "\n";
        m_out_stream << "No secondary optimum was found.\n";
        m_out_stream << "The task is not solveable given the provided constraints.";
    }

    void printFirstToSecondStageTransfer() override
    {
        m_out_stream << "First stage is finished.\n";
        m_out_stream << "Removing unnecessary rows and columns from table.\n";
        m_out_stream << "Starting second stage.\n";
    }

    void printPrimaryOptimumData(const std::vector<VarNumAndVal<T>> &xs,
                                 const std::vector<VarNumAndVal<T>> &vs,
                                 T optimum) override
    {
        m_out_stream << "Optimum data is the following:\n";
        for (size_t i = 0; i < xs.size(); ++i)
            m_out_stream << "x" << xs[i].num + 1 << " = " << stringify(xs[i].val) << "\n";
        for (size_t i = 0; i < vs.size(); ++i)
            m_out_stream << "v" << vs[i].num + 1 << " = " << stringify(vs[i].val) << "\n";
        m_out_stream << "Optimum = " << stringify(optimum) << "\n";
    }

private:
    std::ostream &m_out_stream;

    std::string stringify(T val)
    {
        return std::to_string(val);
    }
};

#endif