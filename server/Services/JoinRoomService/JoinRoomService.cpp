#include "JoinRoomService.hpp"

void JoinRoomService::joinRoom(const int id, const std::string& username)
{
    roomManager->addClientToRoom(id, QString::fromStdString(username));
}