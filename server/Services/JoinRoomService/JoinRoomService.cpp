#include "JoinRoomService.hpp"

void JoinRoomService::joinRoom(const int id, const std::string& login)
{
    roomManager->addClientToRoom(id, QString::fromStdString(login));
}

Client JoinRoomService::findClient(const std::string& login)
{
    return clientManager->getClient(QString::fromStdString(login));
}