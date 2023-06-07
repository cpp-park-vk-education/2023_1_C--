#include "RoomUseCase.hpp"

void RoomUseCase::SendMessage(Message&& message) {
    tempMessage = message;
    roomNetwork_->SendMessage(message);
}

void RoomUseCase::CreateRoom(std::string&& name, std::vector<std::string>&& members) {
    members.push_back(userInfo.login);
    roomNetwork_->CreateRoom(std::move(name), std::move(members));
}

// void RoomUseCase::GetNewMessage(const int roomID) {
//     roomNetwork_->GetNewMessage(roomID);
// }

void RoomUseCase::GetRoomMessages(const int roomID) {
    currentRoomID = roomID;
    roomNetwork_->GetRoomMessages(roomID, userInfo.login);
}

void RoomUseCase::ShowMainPage() {
    roomNetwork_->DisconnectFromRoom();
    RefreshMainPage();
    controller_->ShowMainPage();    
}

void RoomUseCase::ShowMainPage(UserData&& userData) {
    userInfo = userData.info;
    auto rooms = userData.rooms;
    for (const auto& room : userData.rooms)
        userRooms.insert({room.id, room});
    controller_->ShowMainPage();
    mainPage_->ShowRooms(userRooms);
}

void RoomUseCase::AddUser(const int roomID, const std::string& login) {
    roomNetwork_->AddUser(roomID, login);
}

void RoomUseCase::RefreshMainPage() {
    roomNetwork_->RefreshMainPage(userInfo.login);
}

void RoomUseCase::OnSendMessageResponse() {
    roomMessages.push_back(tempMessage);
    roomPage_->ShowSentMessage();
}

void RoomUseCase::OnGetNewMessageResponse(Message&& message) {
    if (!message.content.empty() &&
        message.author != userInfo.login &&
        (roomMessages.empty() || message.id != roomMessages.back().id)) 
    {
        roomMessages.push_back(message);
        roomPage_->ShowNewMessage(std::move(message));
    }
}

void RoomUseCase::OnGetRoomMessagesResponse(std::vector<Message>&& messages) {
    roomNetwork_->ConnectToRoom(currentRoomID, userInfo.login);
    roomMessages = messages;
    controller_->ShowRoomPage();
    roomPage_->SetUserInfo(userInfo);
    roomPage_->ShowRoomInfo(userRooms[currentRoomID]);
    roomPage_->ShowLastMessages(messages);
}

void RoomUseCase::OnCreateRoomResponse(RoomInfo&& roomInfo) {
    roomNetwork_->ConnectToRoom(roomInfo.id, userInfo.login);
    userRooms.insert({roomInfo.id, roomInfo});
    roomPage_->ShowRoomInfo(roomInfo);
    roomPage_->SetUserInfo(userInfo);
    mainPage_->ShowRooms(userRooms); // Add new room on main page
    controller_->ShowRoomPage();
}

void RoomUseCase::OnAddUserResponse(UserInfo&& userInfo) {
    userRooms[currentRoomID].members.push_back(userInfo);
    roomPage_->ShowAddedUser(userInfo);
}

void RoomUseCase::OnRefreshMainPage(UserData&& userData) {
    userRooms.clear();
    for (const auto& room : userData.rooms)
        userRooms.insert({room.id, room});
    mainPage_->ShowRooms(userRooms);
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
