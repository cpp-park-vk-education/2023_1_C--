#pragma once

#include <memory>

#include "IRoomDBManager.hpp"

class DeleteRoomService
{
public:
    DeleteRoomService(std::shared_ptr<IRoomDBManager> roomManager) : roomManager(roomManager){}

    void deleteRoom(const int);

private:
    std::shared_ptr<IRoomDBManager> roomManager;
};