#include "LoginService.hpp"

Client LoginService::getClient(const std::string& login) // NOT SAFE | WIP
{
    return clientManager->getClient(QString::fromStdString(login));
}

std::vector<Room> LoginService::getClientRooms(const std::string& username)
{
    auto rooms = roomManager->getRooms(QString::fromStdString(username));
}