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