#pragma once

#include <memory>
#include <vector>
#include <QVector>

#include "IClientDBManager.hpp"
#include "IRoomDBManager.hpp"

class LoginService
{
public:
    LoginService(std::shared_ptr<IClientDBManager> clientManager,
        std::shared_ptr<IRoomDBManager> roomManager) :
            clientManager(clientManager), roomManager(roomManager){}

    Client getClient(const std::string&);

    std::vector<Client> getClients(const int);

    std::vector<Room> getClientRooms(const std::string&);

private:
    std::shared_ptr<IClientDBManager> clientManager;

    std::shared_ptr<IRoomDBManager> roomManager;
};