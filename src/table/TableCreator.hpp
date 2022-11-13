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
        auto [varNamesCol, nextLineStart] = parseFirstLine(descriptor);
        std::vector<VarName> varNamesRow;
        std::vector<std::vector<T>> tableValues;
        size_t rows = 0;
        while (nextLineStart != std::string::npos)
        {
            auto [varNameRow, rowValues, nextLineStartTmp] = parseLine(descriptor, nextLineStart);
            nextLineStart = nextLineStartTmp;
            if (varNameRow.type != VarType::OTHER)
                varNamesRow.push_back(varNameRow);
            if (rowValues.size() != varNamesCol.size() + 1)
                throw LPException("Error parsing table values.");
            tableValues.push_back(rowValues);
            ++rows;
        }
        return Table<T>(rows,
                        varNamesCol.size() + 1,
                        varNamesCol,
                        varNamesRow,
                        tableValues);
    }

private:
    std::pair<std::vector<VarName>, size_t> parseFirstLine(const std::string &descriptor) const
    {
        size_t start = glp::nextMeaningfulChar(descriptor, 0);
        std::vector<VarName> varNames;
        do
        {
            size_t end = glp::nextSpace(descriptor, start);
            std::string token = descriptor.substr(start, end - start);
            VarName varName = parseVarName(token);
            if (varName.type != VarType::OTHER)
                varNames.push_back(varName);
            start = glp::nextMeaningfulChar(descriptor, end);
            if (start == std::string::npos)
                throw LPException("Invalid table text.");
        } while (descriptor.at(start) != '\n');
        return std::pair<std::vector<VarName>, size_t>(std::move(varNames), start + 1);
    }

    std::tuple<VarName, std::vector<T>, size_t> parseLine(const std::string &descriptor, size_t lineStart) const
    {
        size_t end = glp::nextSpace(descriptor, lineStart);
        std::string token = descriptor.substr(lineStart, end - lineStart);
        VarName varName = parseVarName(token);

        std::vector<T> values;
        size_t start = glp::nextMeaningfulChar(descriptor, end);
        while (start != std::string::npos && descriptor.at(start) != '\n')
        {
            end = glp::nextSpace(descriptor, start);
            std::string valueToken = descriptor.substr(start, end - start);
            values.push_back(stoT(valueToken));
            start = glp::nextMeaningfulChar(descriptor, end);
        }
        size_t nextLineStart = start == std::string::npos ? std::string::npos : start + 1;
        return std::tuple<VarName, std::vector<T>, size_t>(std::move(varName), std::move(values), nextLineStart);
    }

    VarName parseVarName(const std::string &token) const
    {
        VarName varName{0, VarType::OTHER};
        size_t numI = 1;
        // 1. Set VarType
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
        case 'b':
        case 'B':
        case '-':
        case 'z':
        case 'Z':
            varName.type = VarType::OTHER;
            return varName;
        default:
            throw LPException("Bad Var Name token.");
        }
        // 2. Set var number
        std::string varNumberStr = token.substr(numI);
        try
        {
            varName.num = std::stoi(varNumberStr) - 1;
        }
        catch (const std::invalid_argument &e)
        {
            throw LPException("Bad Var Name token.");
        }
        catch (const std::out_of_range &e)
        {
            throw LPException("Bad Var Name token.");
        }
        return varName;
    }

    T stoT(const std::string &token) const;
};

template <>
float TableCreatorText<float>::stoT(const std::string &token) const
{
    return std::stof(token);
}

template <>
double TableCreatorText<double>::stoT(const std::string &token) const
{
    return std::stod(token);
}

template <>
long double TableCreatorText<long double>::stoT(const std::string &token) const
{
    return std::stold(token);
}

#endif