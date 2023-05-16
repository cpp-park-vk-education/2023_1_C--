#pragma once

#include <memory>
#include <vector>
#include <QDebug>

#include "IClientDBManager.hpp"
#include "IRoomDBManager.hpp"

class CreateRoomService
{
public:
    CreateRoomService(std::shared_ptr<IClientDBManager> clientManager, std::shared_ptr<IRoomDBManager> roomManager)
        : clientManager(clientManager), roomManager(roomManager){}

    void CreateRoomWithUsers(const std::vector<std::string>& logins, const std::string roomName);

    bool isClientExists(const std::string& login);
private:
    std::shared_ptr<IClientDBManager> clientManager;

    std::shared_ptr<IRoomDBManager> roomManager;
};