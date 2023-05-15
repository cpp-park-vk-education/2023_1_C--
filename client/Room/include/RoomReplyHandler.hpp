#pragma once
#include "IRoomReplyHandler.hpp"
#include "IRoomSwitcher.hpp"
#include "IRoomPageUi.hpp"

class RoomReplyHandler : public IRoomReplyHandler {
public:
    void OnAddUserResponse(const int statusCode, const RoomInfo& roomInfo) override;
    void OnSendMessageResponse(const int statusCode) override;
    void OnGetMessagesResponse(const int statusCode, const std::vector<Message>& messages) override;
    void OnCreateRoomResponse(const int statusCode, RoomData room) override;

    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

    void SetRoomPageUi(IRoomPageUi* roomUi) {
        roomUi_ = roomUi;
    }

private:
    IRoomPageUi* roomUi_;
    IRoomSwitcherSPtr roomSwitcher_;
};
