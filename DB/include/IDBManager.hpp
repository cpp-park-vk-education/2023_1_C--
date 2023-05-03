#pragma once

#include <string>
#include <vector>

class IDBManager {
public:
    virtual int connect(const std::string&) = 0;

    virtual std::vector<std::vector<std::string>> exec(const std::string&) = 0;
};
