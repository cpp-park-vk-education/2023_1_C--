#include "RoomNetwork.hpp"
#include "Communication.hpp"

const std::string SEND_MESSAGE_URL = "/send";
const std::string CREATE_ROOM_URL = "/create";
const std::string GET_ROOM_MESSAGES_URL = "/history";
const std::string GET_MESSAGE_URL = "/getmsg";

RoomNetwork::RoomNetwork() {
    createRoomCallback = Callback (
        [this](IResponseUPtr response) {
           return this->OnCreateRoomResponse(std::move(response)); 
        }
    ); 

    sendMessageCallback = Callback (
        [this](IResponseUPtr response) {
           return this->OnSendMessageResponse(std::move(response)); 
        }
    );

    getNewMessageCallback  = Callback (
        [this](IResponseUPtr response) {
           return this->OnGetNewMessageResponse(std::move(response)); 
        }
    ); 

    getRoomMessagesCallback = Callback (
        [this](IResponseUPtr response) {
           return this->OnGetRoomMessagesResponse(std::move(response)); 
        }
    );
}

void RoomNetwork::CreateRoom(const RoomInfo& roomInfo) {
    auto request = CreateRequest(CREATE_ROOM_URL);
    auto byteArray = serializer_->SerializeRoomInfo(roomInfo);
    networkManager_->Post(request, GetQByteArray(byteArray), createRoomCallback);
}

void RoomNetwork::SendMessage(const Message& message) {
    auto request = CreateRequest(SEND_MESSAGE_URL);
    auto byteArray = serializer_->SerializeMessage(message);
    networkManager_->Post(request, GetQByteArray(byteArray), sendMessageCallback);    
}

void RoomNetwork::GetNewMessage(const int roomID) {
    auto request = CreateRequest(GET_MESSAGE_URL);
    auto byteArray = serializer_->SerializeID(roomID);
    networkManager_->Post(request, GetQByteArray(byteArray), getNewMessageCallback);
}
void RoomNetwork::GetRoomMessages(const int roomID) {
    auto request = CreateRequest(GET_ROOM_MESSAGES_URL);
    auto byteArray = serializer_->SerializeID(roomID);
    networkManager_->Post(request, GetQByteArray(byteArray), getRoomMessagesCallback); // Get()
}

void RoomNetwork::OnCreateRoomResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeCreateRoomResponse(response->GetBody());
        replyHandler_->OnCreateRoomResponse(200, std::move(data));
    } else {
        replyHandler_->OnCreateRoomResponse(statusCode, RoomInfo{});
    }
}

void RoomNetwork::OnSendMessageResponse(IResponseUPtr response) {
    replyHandler_->OnSendMessageResponse(response->GetStatus());
}

void RoomNetwork::OnGetNewMessageResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeMessage(response->GetBody());
        replyHandler_->OnGetNewMessageResponse(200, std::move(data));
    } else {
        replyHandler_->OnGetNewMessageResponse(statusCode, Message{});
    }
}

void RoomNetwork::OnGetRoomMessagesResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeRoomMessages(response->GetBody());    
        replyHandler_->OnGetRoomMessagesResponse(200, std::move(data));
    } else {
        replyHandler_->OnGetRoomMessagesResponse(statusCode, std::vector<Message>{});
    }
}
