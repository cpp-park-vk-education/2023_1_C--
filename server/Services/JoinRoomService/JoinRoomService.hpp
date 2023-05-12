#pragma once

#include <memory>

#include "IRoomDBManager.hpp"

class JoinRoomService
{
public:
    JoinRoomService(std::shared_ptr<IRoomDBManager> roomManager) : roomManager(roomManager){}

    void GetRoom(const int);

private:
    std::shared_ptr<IRoomDBManager> roomManager;
};