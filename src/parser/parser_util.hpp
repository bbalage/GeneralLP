#ifndef GENERALLP_PARSER_PARSERUTIL_HPP
#define GENERALLP_PARSER_PARSERUTIL_HPP

#include <cctype>
#include <string>

namespace glp
{
    /**
     * Returns the next index in the text, where there is a meaningful, not ignored character,
     * such as newline or text.
     *
     * @param text The string to search.
     * @param from The index to start searching from.
     * @return size_t The index marking the next meaningful character or string::npos if the end of the string is reached.
     */
    size_t nextMeaningfulChar(const std::string &text, size_t from)
    {
        for (size_t i = from; i < text.size(); ++i)
        {
            if (!std::isspace(text.at(i)) || text.at(i) == '\n')
                return i;
        }
        return std::string::npos;
    }

    size_t nextSpace(const std::string &text, size_t from)
    {
        for (size_t i = from; i < text.size(); ++i)
        {
            if (std::isspace(text.at(i)))
                return i;
        }
        return std::string::npos;
    }
}

#endif