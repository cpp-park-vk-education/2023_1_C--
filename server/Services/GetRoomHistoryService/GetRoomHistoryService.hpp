#pragma once

#include <memory>
#include <vector>
#include <QVector>

#include "IRoomDBManager.hpp"

class GetRoomHistoryService
{
public:
    GetRoomHistoryService(std::shared_ptr<IRoomDBManager> roomManager) : roomManager(roomManager){}

    std::vector<Message> getMessages(const int id);
private:
    std::shared_ptr<IRoomDBManager> roomManager;
};