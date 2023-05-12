#pragma once
#include <memory>
#include <vector>
#include "RoomData.hpp"
#include "UserData.hpp"


class IRoomSwitcher {
public:
    virtual ~IRoomSwitcher() {}
    virtual void ShowMainPage(std::vector<IRoomUPtr> rooms,
                              const UserInfo& userInfo) = 0;
    virtual void ShowRoom(IRoomUPtr room) = 0;
    virtual void ShowRoomInfo(const RoomInfo& roomInfo) = 0;
    virtual void ShowLastMessages(const std::vector<Message>& messages) = 0;
    virtual void ShowOldMessages(const std::vector<Message>& messages) = 0;

};

using IRoomSwitcherUPtr = std::unique_ptr<IRoomSwitcher>;
