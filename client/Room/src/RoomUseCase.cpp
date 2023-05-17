#include "RoomUseCase.hpp"


void RoomUseCase::SendMessage(const Message& message) {
    roomNetwork_->SendMessage(message);
}

void RoomUseCase::CreateRoom(const RoomInfo& roomInfo) {
    roomNetwork_->CreateRoom(roomInfo); 
}

void RoomUseCase::GetNewMessage(const int roomID) {
    roomNetwork_->GetNewMessage(roomID); 
}

void RoomUseCase::GetRoomMessage(const int roomID) {
    roomNetwork_->GetRoomMessages(roomID);
}

void RoomUseCase::OnSendMessageResponse(int statusCode) {}

void RoomUseCase::OnGetNewMessageResponse(int statusCode, const Message& message)
{
}

void RoomUseCase::OnGetRoomMessagesResponse(int statusCode, const std::vector<Message> messages) {
    if (statusCode == 200) {
        roomSwitcher_->ShowLastMessages(messages);
    }

}

void RoomUseCase::OnCreateRoomResponse(int statusCode, const RoomData& roomData) {
    if (statusCode == 200) {
        //roomSwitcher_->ShowRoom(roomData);
    }
}
