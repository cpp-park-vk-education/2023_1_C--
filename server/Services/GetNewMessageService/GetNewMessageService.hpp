#pragma once

#include <memory>

#include "IRoomDBManager.hpp"

class GetNewMessageService
{
public:
    GetNewMessageService(std::shared_ptr<IRoomDBManager> roomManager) : roomManager(roomManager){}

    Message getNewMessage(const int);

private:
    std::shared_ptr<IRoomDBManager> roomManager;
};