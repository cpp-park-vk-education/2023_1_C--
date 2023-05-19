#include "RoomUseCase.hpp"

RoomInfo RoomUseCase::FindRoomInfo(const int roomID) {
    for (const auto room : userData_.rooms)
        if (room.id == roomID)
            return room;
    return RoomInfo{};
}

void RoomUseCase::SendMessage(Message&& message) {
    tempMessage = message;
    roomNetwork_->SendMessage(message);
}

void RoomUseCase::CreateRoom(RoomInfo&& roomInfo) {
    roomNetwork_->CreateRoom(roomInfo); 
}

void RoomUseCase::GetNewMessage(const int roomID) {
    roomNetwork_->GetNewMessage(roomID); 
}

void RoomUseCase::GetRoomMessages(const int roomID) {
    room = FindRoomInfo(roomID);
    roomNetwork_->GetRoomMessages(roomID);
}

void RoomUseCase::ShowMainPage(UserData&& userData) {
    userData_ = userData;
    controller_->ShowMainPage();
    mainPage_->ShowRooms(userData.rooms);
}

void RoomUseCase::AddUser(const int roomID, const std::string& login) {
    roomNetwork_->AddUser(roomID, login);
}

void RoomUseCase::OnSendMessageResponse(const int statusCode) {
    if (statusCode == 200) {
        roomMessages.push_back(tempMessage);
        roomPage_->ShowSentMessage();
    }
}

void RoomUseCase::OnGetNewMessageResponse(const int statusCode, Message&& message) {
    if (statusCode == 200 && !message.content.empty() &&
        message.author != userData_.info.login &&
        message.id != roomMessages.back().id) 
    {
        roomMessages.push_back(message);
        roomPage_->ShowNewMessage(std::move(message));
    }
}

void RoomUseCase::OnGetRoomMessagesResponse(const int statusCode, std::vector<Message>&& messages) {
    if (statusCode == 200) {
        roomMessages = messages;
        controller_->ShowRoomPage();
        roomPage_->SetData(room, userData_.info);
        roomPage_->ShowRoomInfo(room);
        roomPage_->ShowLastMessages(std::move(messages));
    }
}

void RoomUseCase::OnCreateRoomResponse(const int statusCode, RoomInfo&& roomInfo) {
    if (statusCode == 200) {
        userData_.rooms.push_back(roomInfo);
        roomPage_->ShowRoomInfo(roomInfo);
    }
}

void RoomUseCase::OnAddUserResponse(const int statusCode, UserInfo&& userInfo) {
    // if (statusCode == 200)
    //     roomPage_->ShowAddedUser();
}

