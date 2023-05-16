#pragma once
#include <memory>
#include <vector>
#include "RoomData.hpp"
#include "AccountData.hpp"

class IRoomSwitcher {
public:
    virtual ~IRoomSwitcher() {}
    virtual void ShowMainPage(std::vector<RoomData> rooms,
                              const UserInfo& userInfo) = 0;
    virtual void ShowRoom(const RoomData& roomData, const UserInfo userInfo) = 0;
    virtual void ShowLastMessages(const std::vector<Message>& messages) = 0;
    virtual void ShowOldMessages(const std::vector<Message>& messages) = 0;
    virtual void ShowRoomSearchPage() = 0;
    virtual void ShowRoomCreationPage() = 0;
    virtual void BackOnMainPage() = 0;
};

using IRoomSwitcherSPtr = std::shared_ptr<IRoomSwitcher>;
