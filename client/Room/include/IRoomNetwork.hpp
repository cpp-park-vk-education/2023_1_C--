#pragma once
#include <memory>
#include "RoomData.hpp"

class IRoomNetwork {
public:
    virtual ~IRoomNetwork() {}
    virtual void CreateRoom(const RoomInfo& roomInfo) = 0;
    virtual void SendMessage(const Message& message) = 0;
    virtual void GetNewMessage(const int roomID) = 0;
    virtual void GetRoomMessages(const int roomID) = 0;
    virtual void AddUser(const int roomID, const std::string& login) = 0;
};

using IRoomNetworkSPtr = std::shared_ptr<IRoomNetwork>;
