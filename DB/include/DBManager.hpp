#pragma once

#include "IDBManager.hpp"

class DBManager: public IDBManager {
public:
    DBManager();

    int connect(const std::string &) override;

    std::vector<std::vector<std::string>> exec(const std::string&) override;
};
