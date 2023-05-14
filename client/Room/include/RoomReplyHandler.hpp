#pragma once
#include "IRoomReplyHandler.hpp"
#include "IRoomSwitcher.hpp"

class RoomReplyHandler : public IRoomReplyHandler {
public:
    void OnAddUserResponse(unsigned int statusCode, const RoomInfo& roomInfo) override;
    void OnSendMessageResponse(unsigned int statusCode, const std::vector<Message>& messages) override;
    void OnGetMessagesResponse(unsigned int statusCode, const std::vector<Message>& messages) override;
    void OnCreateRoomResponse(unsigned int statusCode, RoomData room) override;

    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

private:
    IRoomSwitcherSPtr roomSwitcher_;
};
