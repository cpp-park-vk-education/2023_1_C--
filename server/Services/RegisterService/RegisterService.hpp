#pragma once

#include <memory>
#include <QCryptographicHash>

#include "IClientDBManager.hpp"

class RegisterService
{
public:
    RegisterService(std::shared_ptr<IClientDBManager> clientManager) :
        clientManager(clientManager){}

    Client regClient(const std::string& login, const std::string& password, const std::string& username);

private:
    std::shared_ptr<IClientDBManager> clientManager;
};