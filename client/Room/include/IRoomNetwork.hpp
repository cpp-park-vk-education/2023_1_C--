#pragma once
#include <memory>
#include "RoomData.hpp"

class IRoomNetwork {
public:
    virtual ~IRoomNetwork() {}
    virtual void CreateRoom(std::string&& name, 
                            std::vector<std::string>&& members) = 0;
    virtual void SendMessage(const Message& message) = 0;
    virtual void GetNewMessage(const int roomID) = 0;
    virtual void GetRoomMessages(const int roomID, const std::string& login) = 0;
    virtual void AddUser(const int roomID, const std::string& login) = 0;
    virtual void RefreshMainPage(const std::string& login) = 0;
    virtual void DisconnectFromRoom() = 0;
};

using IRoomNetworkSPtr = std::shared_ptr<IRoomNetwork>;
