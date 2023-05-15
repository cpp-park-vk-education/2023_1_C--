#include "RoomReplyHandler.hpp"

void RoomReplyHandler::OnAddUserResponse(const int statusCode, const RoomInfo& roomInfo) {
    // if (statusCode == 200)
    //     roomSwitcher_->ShowRoomInfo(roomInfo);
}

void RoomReplyHandler::OnSendMessageResponse(const int statusCode) {
    if (statusCode == 200)
        roomUi_->ShowSentMessage();
}

void RoomReplyHandler::OnGetMessagesResponse(const int statusCode, const std::vector<Message>& messages) {
    if (statusCode == 200)
        roomSwitcher_->ShowOldMessages(messages);
}

void RoomReplyHandler::OnCreateRoomResponse(const int statusCode, RoomData room) {
    if (statusCode == 200)
        roomSwitcher_->ShowRoom(room);
}
