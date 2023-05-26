#include "RoomUseCase.hpp"

RoomInfo RoomUseCase::FindRoomInfo(const int roomID) {
    for (const auto& room : data.rooms)
        if (room.id == roomID)
            return room;
    return RoomInfo{};
}

void RoomUseCase::AddUserIntoRoom(UserInfo&& userInfo) {
    const auto roomID = room.id;
    for (auto& room : data.rooms)
        if (room.id == roomID) {
            room.members.push_back(userInfo);
            return;
        }
}

void RoomUseCase::SendMessage(Message&& message) {
    tempMessage = message;
    roomNetwork_->SendMessage(message);
}

void RoomUseCase::CreateRoom(std::string&& name,
                             std::vector<std::string>&& members) 
{
    members.push_back(data.info.login);
    roomNetwork_->CreateRoom(std::move(name), std::move(members));
}

void RoomUseCase::GetNewMessage(const int roomID) {
    roomNetwork_->GetNewMessage(roomID);
}

void RoomUseCase::GetRoomMessages(const int roomID) {
    room = FindRoomInfo(roomID);
    roomNetwork_->GetRoomMessages(roomID, data.info.login);
}

void RoomUseCase::ShowMainPage() {
    roomNetwork_->DisconnectFromRoom();
    controller_->ShowMainPage();    
}

void RoomUseCase::ShowMainPage(UserData&& userData) {
    data = userData;
    controller_->ShowMainPage();
    mainPage_->ShowRooms(userData.rooms);
}

void RoomUseCase::AddUser(const int roomID, const std::string& login) {
    roomNetwork_->AddUser(roomID, login);
}

void RoomUseCase::RefreshMainPage() {
    roomNetwork_->RefreshMainPage(data.info.login);
}

void RoomUseCase::OnSendMessageResponse() {
    roomMessages.push_back(tempMessage);
    roomPage_->ShowSentMessage();
}

void RoomUseCase::OnGetNewMessageResponse(Message&& message) {
    if (!message.content.empty() &&
        message.author != data.info.login &&
        (roomMessages.empty() || message.id != roomMessages.back().id)) 
    {
        roomMessages.push_back(message);
        roomPage_->ShowNewMessage(std::move(message));
    }
}

void RoomUseCase::OnGetRoomMessagesResponse(std::vector<Message>&& messages) {
    roomNetwork_->ConnectToRoom(room.id, data.info.login);
    roomMessages = messages;
    controller_->ShowRoomPage();
    roomPage_->SetUserInfo(data.info);
    roomPage_->ShowRoomInfo(room);
    roomPage_->ShowLastMessages(messages);
}

void RoomUseCase::OnCreateRoomResponse(RoomInfo&& roomInfo) {
    roomNetwork_->ConnectToRoom(roomInfo.id, data.info.login);
    data.rooms.push_back(roomInfo);
    roomPage_->ShowRoomInfo(roomInfo);
    roomPage_->SetUserInfo(data.info);
    mainPage_->ShowRooms(data.rooms); // Add new room on main page
    controller_->ShowRoomPage();
}

void RoomUseCase::OnAddUserResponse(UserInfo&& userInfo) {
    roomPage_->ShowAddedUser(userInfo);
    AddUserIntoRoom(std::move(userInfo));
}

void RoomUseCase::OnRefreshMainPage(UserData&& userData) {
    data.rooms = userData.rooms; // required only rooms
    mainPage_->ShowRooms(data.rooms);
}

void RoomUseCase::ShowMainPageError(std::string&& error) {
    mainPage_->ShowError(error);
}

void RoomUseCase::ShowRoomPageError(std::string&& error) {
    roomPage_->ShowError(error);
}

void RoomUseCase::ShowRoomCreationPageError(std::string&& error) {
    roomCreationPage_->ShowError(error);
}
