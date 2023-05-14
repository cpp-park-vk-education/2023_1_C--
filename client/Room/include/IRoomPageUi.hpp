#pragma once
#include "RoomData.hpp"
#include <vector>
#include <memory>

class IRoomPageUi {
public:
    virtual ~IRoomPageUi() {}
    virtual void ShowRoomInfo(const RoomInfo& roomInfo) = 0;
    virtual void ShowRoomName(const std::string& name) = 0;
    virtual void ShowLastMessages(const std::vector<Message>& messages) = 0;
    virtual void ShowOldMessages(const std::vector<Message>& messages) = 0;
    
};

using IRoomPageUiSPtr = std::shared_ptr<IRoomPageUi>;
