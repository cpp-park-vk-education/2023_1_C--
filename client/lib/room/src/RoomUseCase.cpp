#include "RoomUseCase.hpp"

void RoomUseCase::AddUser(const std::string& login) {
    roomNetwork_->AddUser(login);
}

void RoomUseCase::SendMessage(const Message& message) {
    roomNetwork_->SendMessage(message);
}

void RoomUseCase::CreateRoom(const RoomInfo& roomInfo) {
    roomNetwork_->CreateRoom(roomInfo); 
}

void RoomUseCase::GetMessages(const size_t messageId) {
    roomNetwork_->GetMessages(messageId); 
}
