#include "parser_util.hpp"

size_t glp::nextMeaningfulChar(const std::string &text, size_t from)
{
    for (size_t i = from; i < text.size(); ++i)
    {
        if (!std::isspace(text.at(i)) || text.at(i) == '\n')
            return i;
    }
    return std::string::npos;
}

size_t glp::nextSpace(const std::string &text, size_t from)
{
    for (size_t i = from; i < text.size(); ++i)
    {
        if (std::isspace(text.at(i)))
            return i;
    }
    return std::string::npos;
}