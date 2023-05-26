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

    refreshMainPageCallback = Callback(
        [this](IResponseUPtr response) {
           return this->OnRefreshMainPageResponse(std::move(response));
        }
    );

    requestNewMessage = std::function<void(const int)> (
        [this](const int roomID) {
            auto request = createRequest(GET_MESSAGE_URL);
            auto byteArray = serializer_->SerializeID(roomID);
            request.SetBody(std::move(byteArray));
            networkManager_->Post(std::make_unique<Request>(request), getNewMessageCallback); // Get request
        }
    );
}

void RoomNetwork::CreateRoom(std::string&& name, 
                             std::vector<std::string>&& members) 
{
    auto request = createRequest(CREATE_ROOM_URL);
    auto byteArray = serializer_->SerializeRoomCreation(
        std::move(name), std::move(members)
    );
    request.SetBody(std::move(byteArray));
    networkManager_->Post(std::make_unique<Request>(request), createRoomCallback);
}

void RoomNetwork::SendMessage(const Message& message) {
    auto request = createRequest(SEND_MESSAGE_URL);
    auto byteArray = serializer_->SerializeMessage(message);
    request.SetBody(std::move(byteArray));
    networkManager_->Post(std::make_unique<Request>(request), sendMessageCallback);
}

void RoomNetwork::GetNewMessage(const int roomID) {}

void RoomNetwork::GetRoomMessages(const int roomID, const std::string& login) {
    auto request = createRequest(GET_ROOM_MESSAGES_URL);
    auto byteArray = serializer_->SerializeID(roomID);
    request.SetBody(std::move(byteArray));
    networkManager_->Post(std::make_unique<Request>(request), getRoomMessagesCallback); // Get request
}

void RoomNetwork::RefreshMainPage(const std::string& login) {
    auto request = createRequest(REFRESH_URL);
    LoginData data; 
    data.login = login;
    auto byteArray = serializer_->SerializeLoginData(data);
    request.SetBody(std::move(byteArray));
    networkManager_->Post(std::make_unique<Request>(request), refreshMainPageCallback); // Get request
}

void RoomNetwork::AddUser(const int roomID, const std::string& login) {
    auto request = createRequest(JOIN_URL);
    auto byteArray = serializer_->SerializeJoiningUser(roomID, login);
    request.SetBody(std::move(byteArray));
    networkManager_->Post(std::make_unique<Request>(request), addUserCallback);  
}

void RoomNetwork::ConnectToRoom(const int roomID, const std::string& login) {
    tcpConnection_->ConnectToHost(roomID, login, requestNewMessage);
}

void RoomNetwork::DisconnectFromRoom() {
    tcpConnection_->DisconnectFromHost();
}

void RoomNetwork::OnCreateRoomResponse(IResponseUPtr response) {
    if (response->GetStatus()) {
        auto data = deserializer_->DeserializeCreateRoomResponse(response->GetBody());
        replyHandler_->OnCreateRoomResponse(std::move(data));
    } else {
        replyHandler_->ShowRoomCreationPageError("Room wasn't created: " + response->GetDescreption());
    }
}

void RoomNetwork::OnSendMessageResponse(IResponseUPtr response) {
    if (response->GetStatus())
        replyHandler_->OnSendMessageResponse();
    else 
        replyHandler_->ShowRoomPageError("Message wasn't sent: " + response->GetDescreption());
}

void RoomNetwork::OnGetNewMessageResponse(IResponseUPtr response) {
    if (response->GetStatus()) {
        auto data = deserializer_->DeserializeMessage(response->GetBody());
        replyHandler_->OnGetNewMessageResponse(std::move(data));
    }
}

void RoomNetwork::OnGetRoomMessagesResponse(IResponseUPtr response) {
    if (response->GetStatus()) {
        auto data = deserializer_->DeserializeRoomMessages(response->GetBody());    
        replyHandler_->OnGetRoomMessagesResponse(std::move(data));
    } else {
        replyHandler_->ShowMainPageError("Room history wasn't recieved: " + response->GetDescreption());
    }
}

void RoomNetwork::OnAddUserResponse(IResponseUPtr response) {
    if (response->GetStatus()) {
        auto data = deserializer_->DeserializeUserInfo(response->GetBody());    
        replyHandler_->OnAddUserResponse(std::move(data));
    } else {
        replyHandler_->ShowRoomPageError("User wasn't added: " + response->GetDescreption());
    }
}

void RoomNetwork::OnRefreshMainPageResponse(IResponseUPtr response) {
    if (response->GetStatus()) {
        auto data = deserializer_->DeserializeUserData(response->GetBody());
        replyHandler_->OnRefreshMainPage(std::move(data));
    } else {
        replyHandler_->ShowMainPageError("Update wasn't complited: " + response->GetDescreption());
    }
}
