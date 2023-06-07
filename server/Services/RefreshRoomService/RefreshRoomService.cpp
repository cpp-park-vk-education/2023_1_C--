#include "RefreshRoomService.hpp"

Client RefreshRoomService::getClient(const std::string& login)
{
    return clientManager->getClient(QString::fromStdString(login));
}

std::vector<Room> RefreshRoomService::getClientRooms(const std::string& username)
{
    auto rooms = roomManager->getRooms(QString::fromStdString(username));

    return rooms.toStdVector();
}

std::vector<Client> RefreshRoomService::getClients(const int id)
{
    auto clients = clientManager->getClientsInRoom(id);

    return clients.toStdVector();
}