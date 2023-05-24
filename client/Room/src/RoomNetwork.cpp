#include "RoomNetwork.hpp"
#include "AccountData.hpp"
#include "Communication.hpp"

const std::string SEND_MESSAGE_URL = "/send";
const std::string CREATE_ROOM_URL = "/create";
const std::string GET_ROOM_MESSAGES_URL = "/history";
const std::string GET_MESSAGE_URL = "/getmsg";
const std::string JOIN_URL = "/join";
const std::string REFRESH_URL = "/refresh";

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

    addUserCallback = Callback (
        [this](IResponseUPtr response) {
           return this->OnAddUserResponse(std::move(response)); 
        }
    );

    requestNewMessage = std::function<void(const int)> (
        [this](const int roomID) {
            auto request = CreateRequest(GET_MESSAGE_URL);
            auto byteArray = serializer_->SerializeID(roomID);
            networkManager_->Post(request, GetQByteArray(byteArray), getNewMessageCallback);
        }
    );

    refreshMainPageCallback = Callback(
        [this](IResponseUPtr response) {
           return this->OnRefreshMainPageResponse(std::move(response));
        }
    );
}

void RoomNetwork::CreateRoom(std::string&& name, 
                             std::vector<std::string>&& members) 
{
    auto request = CreateRequest(CREATE_ROOM_URL);
    auto byteArray = serializer_->SerializeRoomCreation(
        std::move(name), std::move(members)
    );
    networkManager_->Post(request, GetQByteArray(byteArray), createRoomCallback);
}

void RoomNetwork::SendMessage(const Message& message) {
    auto request = CreateRequest(SEND_MESSAGE_URL);
    auto byteArray = serializer_->SerializeMessage(message);
    networkManager_->Post(request, GetQByteArray(byteArray), sendMessageCallback);    
}

void RoomNetwork::GetNewMessage(const int roomID) {}

void RoomNetwork::GetRoomMessages(const int roomID, const std::string& login) {
    auto request = CreateRequest(GET_ROOM_MESSAGES_URL);
    auto byteArray = serializer_->SerializeID(roomID);
    networkManager_->Post(request, GetQByteArray(byteArray), getRoomMessagesCallback); // Get()
    tcpConnection_->ConnectToHost(roomID, login, requestNewMessage);
}

void RoomNetwork::RefreshMainPage(const std::string& login) {
    auto request = CreateRequest(REFRESH_URL);
    LoginData data; 
    data.login = login;
    auto byteArray = serializer_->SerializeLoginData(data);
    networkManager_->Post(request, GetQByteArray(byteArray), refreshMainPageCallback); // Get()
}

void RoomNetwork::DisconnectFromRoom() {
    tcpConnection_->DisconnectFromHost();
}

void RoomNetwork::AddUser(const int roomID, const std::string& login) {
    auto request = CreateRequest(JOIN_URL);
    auto byteArray = serializer_->SerializeJoiningUser(roomID, login);
    networkManager_->Post(request, GetQByteArray(byteArray), addUserCallback); 
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

void RoomNetwork::OnAddUserResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeUserInfo(response->GetBody());    
        replyHandler_->OnAddUserResponse(200, std::move(data));
    } else {
        replyHandler_->OnAddUserResponse(statusCode, UserInfo{});
    }
}

void RoomNetwork::OnRefreshMainPageResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        auto data = deserializer_->DeserializeUserData(response->GetBody());
        replyHandler_->OnRefreshMainPage(200, std::move(data));
    } else {
        replyHandler_->OnRefreshMainPage(statusCode, UserData{});
    }
}