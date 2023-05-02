#pragma once

#include "IDbManager.hpp"

class IClientDbManager
{
public:
    virtual std::string GetClient(const std::string& login, const std::string& password) = 0;
};