#include "CreateRoomService.hpp"

bool CreateRoomService::isClientExists(const std::string& login)
{
    auto client = clientManager->getClient(QString::fromStdString(login));

    if (!client.login.size())
        return false;
    
    return true;
}

void CreateRoomService::CreateRoomWithUsers(const std::vector<std::string>& logins, const std::string roomName)
{
    auto it = logins.begin();

    auto room = roomManager->insertRoom(QString::fromStdString(*it++), QString::fromStdString(roomName));

    for (it; it != logins.end(); ++it)
    {
        roomManager->addClientToRoom(room.ID, QString::fromStdString(*it));
    }

    return Room;
}

std::vector<Client> CreateRoomService::getClientsByLogin(const std::vector<std::string>& logins)
{
    std::vector<Client> clients;

    for (const auto& login : logins)
        clients.push_back(
            clientManager->getClient(QString::fromStdString(login))
        );

    return clients;
}