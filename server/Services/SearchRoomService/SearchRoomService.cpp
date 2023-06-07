#include "SearchRoomService.hpp"

std::vector<Room> SearchRoomService::search(const std::string& roomName)
{
    return roomManager->searchRooms(QString::fromStdString(roomName)).toStdVector();
}

std::vector<Client> SearchRoomService::getClients(const int id)
{
    return clientManager->getClientsInRoom(id).toStdVector();
}