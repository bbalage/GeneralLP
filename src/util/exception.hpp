#ifndef GENERALLP_UTIL_EXCEPTION_HPP
#define GENERALLP_UTIL_EXCEPTION_HPP

#include <exception>
#include <string>

class LPException : public std::exception
{
public:
    LPException(std::string msg) : m_msg(msg) {}

    const char *what()
    {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

#endif