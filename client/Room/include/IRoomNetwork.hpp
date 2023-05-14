#pragma once
#include <memory>
#include "RoomData.hpp"

class IRoomNetwork {
public:
    virtual ~IRoomNetwork() {}
    virtual void AddUser(const std::string& login) = 0;
    virtual void SendMessage(const Message& message) = 0;
    virtual void CreateRoom(const RoomInfo& roomInfo) = 0;
    virtual void GetMessages(const size_t messageId) = 0;
};

using IRoomNetworkSPtr = std::shared_ptr<IRoomNetwork>;
