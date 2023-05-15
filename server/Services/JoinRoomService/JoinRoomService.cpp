#include "JoinRoomService.hpp"

void JoinRoomService::joinRoom(const int id, const std::string& login)
{
    roomManager->addClientToRoom(id, QString::fromStdString(login));
}