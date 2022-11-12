#ifndef GENERALLP_TABLE_TABLECREATOR_HPP
#define GENERALLP_TABLE_TABLECREATOR_HPP

#include <cctype>

#include "Table.hpp"
#include "../parser/parser_util.hpp"

template <class T>
class TableCreator
{
public:
    TableCreator() {}
    virtual ~TableCreator() {}
    TableCreator(const TableCreator &) = delete;
    TableCreator &operator=(const TableCreator &) = delete;
    TableCreator(TableCreator &&) = default;
    TableCreator &operator=(TableCreator &&) = default;

    virtual Table<T> createTable(const std::string &descriptor) = 0;
};

template <class T>
class TableCreatorText : public TableCreator<T>
{
public:
    /**
     * @brief Create the table from the descriptor, where the text contains the table directly.
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
    Table<T> createTable(const std::string &descriptor) override
    {

        size_t start;
        while (descriptor.at(start = glp::nextMeaningfulChar(descriptor, 0)) != '\n')
            ;
        do
        {
            size_t end = glp::nextSpace(descriptor, start);
            std::string token = descriptor.substr(start, end - start);
            parseVarName(token);
            size_t start = glp::nextMeaningfulChar(descriptor, end);
            if (start == std::string::npos)
                throw LPException("Invalid table text.");
        } while (descriptor.at(start) != '\n');
    }

private:
    VarName parseVarName(const std::string &token) const
    {
        VarName varName;
        size_t numI = 1;
        switch (token.at(0))
        {
        case 'x':
        case 'X':
            varName.type = VarType::X;
            break;
        case 'v':
        case 'V':
            varName.type = VarType::V;
            break;
        case 'u':
        case 'U':
            if (token.at(1) == '*')
            {
                varName.type = VarType::US;
                numI = 2;
            }
            else
                varName.type = VarType::U;
            break;
        default:
            throw LPException("Bad Var Name token.");
        }
        }
};

#endif