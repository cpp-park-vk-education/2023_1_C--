#pragma once

#include <memory>
#include <vector>
#include <QVector>

#include <IClientDBManager.hpp>
#include "IRoomDBManager.hpp"

class SearchRoomService
{
public:
    SearchRoomService(std::shared_ptr<IClientDBManager> clientManager, std::shared_ptr<IRoomDBManager> roomManager)
        : clientManager(clientManager), roomManager(roomManager){}

    std::vector<Room> search(const std::string&);

    std::vector<Client> getClients(const int);

private:
    std::shared_ptr<IClientDBManager> clientManager;

    std::shared_ptr<IRoomDBManager> roomManager;
};