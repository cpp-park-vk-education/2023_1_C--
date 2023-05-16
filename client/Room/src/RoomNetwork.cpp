#include "RoomNetwork.hpp"
#include "Communication.hpp"

const std::string SEND_MESSAGE_URL = "/send";
const std::string CREATE_ROOM_URL = "/create";
const std::string GET_ROOM_MESSAGES_URL = "/history";
const std::string GET_MESSAGE_URL = "/getmsg";

static QByteArray GetQByteArray(std::vector<char> byteArray) {
    QByteArray qByteArray;
    for (auto byte: byteArray)
        qByteArray.push_back(byte);
    return qByteArray;
}

void RoomNetwork::CreateRoom(const RoomInfo& roomInfo) {
    auto request = CreateRequest("/");
    auto byteArray = serializer_->SerializeRoomInfo(roomInfo);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnCreateRoomResponse(std::move(response)); 
        }
    ); 
    networkManager_->Post(request, GetQByteArray(byteArray), callback);
}

void RoomNetwork::SendMessage(const Message& message) {
    auto request = CreateRequest(SEND_MESSAGE_URL);
    auto byteArray = serializer_->SerializeMessage(message);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnSendMessageResponse(std::move(response)); 
        }
    ); 
    networkManager_->Post(request, GetQByteArray(byteArray), callback);    
}

void RoomNetwork::GetNewMessage(const int roomID) {
    auto request = CreateRequest(GET_MESSAGE_URL);
    auto byteArray = serializer_->SerializeID(roomID);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnGetNewMessageResponse(std::move(response)); 
        }
    ); 
    networkManager_->Post(request, GetQByteArray(byteArray), callback);
}
void RoomNetwork::GetRoomMessages(const int roomID) {
    auto request = CreateRequest(GET_ROOM_MESSAGES_URL);
    auto byteArray = serializer_->SerializeID(roomID);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnGetRoomMessagesResponse(std::move(response)); 
        }
    ); 
    networkManager_->Post(request, GetQByteArray(byteArray), callback); // Get()
}

void RoomNetwork::OnCreateRoomResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        RoomData data = deserializer_->DeserializeCreateRoomResponse(response->GetBody());
        replyHandler_->OnCreateRoomResponse(200, data);
    } else {
        replyHandler_->OnCreateRoomResponse(statusCode, RoomData{});
    }
}

void RoomNetwork::OnSendMessageResponse(IResponseUPtr response) {
    replyHandler_->OnSendMessageResponse(response->GetStatus());
}

void RoomNetwork::OnGetNewMessageResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeMessage(response->GetBody());
        replyHandler_->OnGetNewMessageResponse(200, data);
    } else {
        replyHandler_->OnGetNewMessageResponse(statusCode, Message{});
    }
}

void RoomNetwork::OnGetRoomMessagesResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeRoomMessages(response->GetBody());    
        replyHandler_->OnGetRoomMessagesResponse(200, data);
    } else {
        replyHandler_->OnGetRoomMessagesResponse(statusCode, std::vector<Message>{});
    }
}
