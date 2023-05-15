#include "RoomReplyHandler.hpp"

void RoomReplyHandler::OnAddUserResponse(unsigned int statusCode, const RoomInfo& roomInfo) {
    // if (statusCode == 200)
    //     roomSwitcher_->ShowRoomInfo(roomInfo);
}

void RoomReplyHandler::OnSendMessageResponse(unsigned int statusCode, const std::vector<Message>& messages) {
    if (statusCode == 200)
        roomSwitcher_->ShowLastMessages(messages);
}

void RoomReplyHandler::OnGetMessagesResponse(unsigned int statusCode, const std::vector<Message>& messages) {
    if (statusCode == 200)
        roomSwitcher_->ShowOldMessages(messages);
}

void RoomReplyHandler::OnCreateRoomResponse(unsigned int statusCode, RoomData room) {
    if (statusCode == 200)
        roomSwitcher_->ShowRoom(room);
}
