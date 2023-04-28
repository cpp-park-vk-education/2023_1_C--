#pragma once

#include <string>

class IDbManager
{
public:
    virtual int conect(const std::string&) = 0;
};