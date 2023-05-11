#pragma once

#include <memory>

#include "IRoomDBManager.hpp"

class CreateRoomService
{
public:
    CreateRoomService(std::shared_ptr<IRoomDBManager> roomManager) : roomManager(roomManager){}

    void CreateRoom(const std::string&);

private:
    std::shared_ptr<IRoomDBManager> roomManager;
};