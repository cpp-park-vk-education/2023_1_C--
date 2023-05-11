#pragma once

#include <memory>

#include "IClientDBManager.hpp"

class LoginService
{
public:
    LoginService(std::shared_ptr<IClientDBManager> clientManager) : clientManager(clientManager){}

    Client getClient(const std::string&);

private:
    std::shared_ptr<IClientDBManager> clientManager;
};