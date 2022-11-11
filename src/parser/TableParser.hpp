#ifndef GENERALLP_PARSER_TABLEPARSER_HPP
#define GENERALLP_PARSER_TABLEPARSER_HPP

#include <cctype>

#include "../table/Table.hpp"
#include "parser_util.hpp"

template <class T>
class TableParser
{
public:
    TableParser() {}
    virtual ~TableParser() {}
    TableParser(const TableParser &) = delete;
    TableParser &operator=(const TableParser &) = delete;
    TableParser(TableParser &&) = default;
    TableParser &operator=(TableParser &&) = default;

    virtual Table<T> parseTable(const std::string &descriptor) = 0;
};

template <class T>
class TableParserText : public TableParser<T>
{
public:
    /**
     * @brief Parse the text into a Table<T>, where the text contains the table directly.
     *
     * Required format of the text is (the number of spaces is ignored):
     *     x1  x2 ... v1 ... b\n
     * u1  2   3  ... -1 ... 20\n
     * u*1 2   3  ... -1 ... 40\n
     * u*2 2   3  ... -1 ... 40\n
     * ...
     * -z  2   3  ... -1 ... 0\n
     * z*  2   3  ... -1 ... 60\n
     *
     * @param descriptor The string describing the table.
     * @return Table<T>
     */
    Table<T> parseTable(const std::string &descriptor) override
    {

        size_t start;
        while (descriptor.at(start = glp::nextMeaningfulChar(descriptor, 0)) != '\n')
            ;
        size_t end = glp::nextSpace(descriptor, start);
        std::string token = descriptor.substr(start, end - start);

        // TODO: Finish this function!
    }

private:
};

#endif