#pragma once

#include <memory>

#include "IRoomDBManager.hpp"

class SendMessageService
{
public:
    SendMessageService(std::shared_ptr<IRoomDBManager> roomManager) : roomManager(roomManager){}

    void SendMessage(const int, const std::string&);

private:
    std::shared_ptr<IRoomDBManager> roomManager;
};