#pragma once

#include <memory>

#include "IRoomDBManager.hpp"

class JoinRoomService
{
public:
    JoinRoomService(std::shared_ptr<IRoomDBManager> roomManager) : roomManager(roomManager){}

    void joinRoom(const int, const std::string&);

private:
    std::shared_ptr<IRoomDBManager> roomManager;
};