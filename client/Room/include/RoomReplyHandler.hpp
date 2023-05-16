#pragma once
#include "IRoomReplyHandler.hpp"
#include "IRoomSwitcher.hpp"
#include "IRoomPageUi.hpp"

class RoomReplyHandler : public IRoomReplyHandler {
public:
    void OnSendMessageResponse(int statusCode) override;
    void OnGetNewMessageResponse(int statusCode, const Message& message) override;
    void OnGetRoomMessagesResponse(int statusCode, const std::vector<Message>) override;
    void OnCreateRoomResponse(int statusCode, const RoomData& roomData) override;

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
