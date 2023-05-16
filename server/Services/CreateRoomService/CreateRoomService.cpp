#include "CreateRoomService.hpp"

bool CreateRoomService::isClientExists(const std::string& login)
{
    auto client = clientManager->getClient(QString::fromStdString(login));

    if (!client.login.size())
        return false;
    
    return true;
}
#include <iostream>
void CreateRoomService::CreateRoomWithUsers(const std::vector<std::string>& logins, const std::string roomName)
{
    auto it = logins.begin();

    qDebug() << logins.size();

    auto room = roomManager->insertRoom(QString::fromStdString(*it++), QString::fromStdString(roomName));

    for (it; it != logins.end(); ++it)
    {
        qDebug() << QString::fromStdString(*it);
        roomManager->addClientToRoom(room.ID, QString::fromStdString(*it));
    }
}