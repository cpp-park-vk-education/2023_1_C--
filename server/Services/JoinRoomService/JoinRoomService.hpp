#pragma once

#include <memory>

#include <IClientDBManager.hpp>
#include "IRoomDBManager.hpp"

class JoinRoomService
{
public:
    JoinRoomService(std::shared_ptr<IClientDBManager> clientManager, std::shared_ptr<IRoomDBManager> roomManager)
    : clientManager(clientManager), roomManager(roomManager){}

    void joinRoom(const int, const std::string&);

    Client findClient(const std::string&);

private:
    std::shared_ptr<IClientDBManager> clientManager;

    std::shared_ptr<IRoomDBManager> roomManager;
};