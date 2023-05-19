#include "RoomUseCase.hpp"

RoomInfo RoomUseCase::FindRoomInfo(const int roomID) {
    for (const auto room : userData_.rooms)
        if (room.id == roomID)
            return room;
    return RoomInfo{};
}

void RoomUseCase::SendMessage(Message&& message) {
    roomNetwork_->SendMessage(message);
}

void RoomUseCase::CreateRoom(RoomInfo&& roomInfo) {
    roomNetwork_->CreateRoom(roomInfo); 
}

void RoomUseCase::GetNewMessage(const int roomID) {
    roomNetwork_->GetNewMessage(roomID); 
}

void RoomUseCase::GetRoomMessages(const int roomID) {
    currentRoom = FindRoomInfo(roomID);
    roomNetwork_->GetRoomMessages(roomID);
}

void RoomUseCase::ShowMainPage(UserData&& userData) {
    userData_ = userData;
    controller_->ShowMainPage();
    mainPage_->ShowRooms(userData.rooms);
}

void RoomUseCase::OnSendMessageResponse(int statusCode) {
    if (statusCode == 200)
        roomPage_->ShowSentMessage();
}

void RoomUseCase::OnGetNewMessageResponse(int statusCode, Message&& message) {
    if (statusCode == 200)
        roomPage_->ShowNewMessage(std::move(message));
}

void RoomUseCase::OnGetRoomMessagesResponse(int statusCode, std::vector<Message>&& messages) {
    if (statusCode == 200) {
        controller_->ShowRoomPage();
        roomPage_->SetData(currentRoom, userData_.info);
        roomPage_->ShowRoomName(currentRoom.name);
        roomPage_->ShowLastMessages(std::move(messages));
    }
}

void RoomUseCase::OnCreateRoomResponse(int statusCode, RoomInfo&& roomInfo) {
    if (statusCode == 200) {
        userData_.rooms.push_back(roomInfo);
        roomPage_->ShowRoomName(roomInfo.name);
    }
}


