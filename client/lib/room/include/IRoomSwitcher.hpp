#pragma once
#include <memory>
#include "UserData.hpp"

class IRoomSwitcher {
public:
    virtual ~IRoomSwitcher() {}
    virtual void ShowMainPage(IUserDataUPtr data) = 0;
    // virtual void ShowRoom() = 0;
    // virtual void ShowRoomInfo() = 0;
};

using IRoomSwitcherUPtr = std::unique_ptr<IRoomSwitcher>;
