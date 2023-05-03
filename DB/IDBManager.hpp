#pragma once

#include <string>

class IDBManager {
public:
    virtual int connect(const std::string&) = 0;
};
