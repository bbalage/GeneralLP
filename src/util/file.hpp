#ifndef GENERALLP_UTIL_FILE_HPP
#define GENERALLP_UTIL_FILE_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace glp
{
    std::string fileContentAsString(const std::string &path)
    {
        std::ifstream infstream(path);
        std::stringstream buffer;
        buffer << infstream.rdbuf();
        std::string output(buffer.str());
        infstream.close();
        return output;
    }
}

#endif