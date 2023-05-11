#pragma once

#include <string>
#include <map>

class IDBManager {
public:
    virtual void connect() = 0;
};