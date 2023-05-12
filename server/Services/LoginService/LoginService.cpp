#include "LoginService.hpp"

Client LoginService::getClient(const std::string& login) // NOT SAFE | WIP
{
    return clientManager->getClient(QString::fromStdString(login));
}