#include "RoomReplyHandler.hpp"

void RoomReplyHandler::OnSendMessageResponse(int statusCode) {}

void RoomReplyHandler::OnGetNewMessageResponse(int statusCode, const Message& message)
{
}

void RoomReplyHandler::OnGetRoomMessagesResponse(int statusCode, const std::vector<Message> messages) {
    if (statusCode == 200) {
        roomSwitcher_->ShowLastMessages(messages);
    }

}

void RoomReplyHandler::OnCreateRoomResponse(int statusCode, const RoomData& roomData) {
    if (statusCode == 200) {
        //roomSwitcher_->ShowRoom(roomData);
    }
}
