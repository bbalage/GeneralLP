#ifndef GENERALLP_TABLE_TABLE_HPP
#define GENERALLP_TABLE_TABLE_HPP

#include <memory>

class Table
{
public:
    virtual ~Table() {}
    Table(Table &&) = default;
    Table &operator=(Table &&) = default;
};

#endif