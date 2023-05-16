#pragma once
#include "RoomData.hpp"
#include "IRoomUseCase.hpp"
#include "IRoomSwitcher.hpp"
#include <vector>
#include <memory>

class IRoomPageUi {
public:
    virtual ~IRoomPageUi() {}
    virtual void ShowSentMessage() = 0;
    virtual void ShowRoomInfo(const RoomInfo& roomInfo) = 0;
    virtual void ShowRoomName(const std::string& name) = 0;
    virtual void ShowLastMessages(const std::vector<Message>& messages) = 0;
    virtual void ShowOldMessages(const std::vector<Message>& messages) = 0;
    virtual void SetUserInfo(const UserInfo& userInfo) = 0;
    virtual void SetRoomData(const RoomData& roomdData) = 0;
    virtual void SetRoomUseCase(IRoomUseCaseSPtr useCase) = 0;
    virtual void SetRoomSwitcher(IRoomSwitcherSPtr switcher) = 0;
};

using IRoomPageUiSPtr = std::shared_ptr<IRoomPageUi>;
