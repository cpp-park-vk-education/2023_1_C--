#pragma once
#include <memory>
#include <vector>
#include "RoomData.hpp"
#include "AccountData.hpp"

class IRoomPage {
public:
    virtual ~IRoomPage() {}
    virtual void ShowSentMessage() = 0;
    virtual void ShowAddedUser(const UserInfo& info) = 0;
    virtual void ShowRoomInfo(const RoomInfo& roomInfo) = 0;
    // virtual void ShowRoomName(const std::string& name) = 0;
    virtual void ShowLastMessages(const std::vector<Message>& messages) = 0;
    // virtual void ShowOldMessages(const std::vector<Message>& messages) = 0;
    virtual void ShowNewMessage(const Message& message) = 0;
    virtual void SetData(const RoomInfo& roomInfo, const UserInfo& userInfo) = 0; 
};

using IRoomPageSPtr = std::shared_ptr<IRoomPage>;
