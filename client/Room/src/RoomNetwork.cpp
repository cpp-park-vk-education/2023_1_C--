#include "RoomNetwork.hpp"
#include "Communication.hpp"

const std::string ADD_USER_URL = "/add";
const std::string SEND_MESSAGE_URL = "/send";
const std::string CREATE_ROOM_URL = "/create";
const std::string GET_MESSAGES_URL = "/get";

void RoomNetwork::AddUser(const std::string& login) {
    Headers headers = {{"Content-Type", "JSON"}};
    auto request = CreateRequest(ADD_USER_URL, headers);
    auto body = requestSerializer_->SerializeString(login);
    request.SetBody(body);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnAddUserResponse(std::move(response)); 
        }
    );
    networkManager_->Post(std::make_unique<Request>(request), callback);
}

void RoomNetwork::SendMessage(const Message& message) {
    Headers headers = {{"Content-Type", "JSON"}};
    auto request = CreateRequest(SEND_MESSAGE_URL, headers);
    auto body = requestSerializer_->SerializeMessage(message);
    request.SetBody(body);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnSendMessageResponse(std::move(response)); 
        }
    );
    networkManager_->Post(std::make_unique<Request>(request), callback);
}

void RoomNetwork::CreateRoom(const RoomInfo& roomInfo) {
    Headers headers = {{"Content-Type", "JSON"}};
    auto request = CreateRequest(CREATE_ROOM_URL, headers);
    auto body = requestSerializer_->SerializeRoomInfo(roomInfo);
    request.SetBody(body);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnCreateRoomResponse(std::move(response)); 
        }
    );
    networkManager_->Post(std::make_unique<Request>(request), callback);
}

void RoomNetwork::GetMessages(const size_t messageId) {
    Headers headers = {
        {"Content-Type", "JSON"},
        {"MessageID", std::to_string(messageId)} 
    };
    auto request = CreateRequest(GET_MESSAGES_URL, headers);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnGetMessagesResponse(std::move(response)); 
        }
    );
    networkManager_->Post(std::make_unique<Request>(request), callback);    
}


void RoomNetwork::OnAddUserResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus(ADD_USER_URL);
    if (statusCode == 200) {
        auto body = response->GetBody();
        auto roomData = responseSerializer_->DeserializeResponse(body);
        replyHandler_->OnAddUserResponse(200, roomData->GetRoomInfo());
    } else {
        replyHandler_->OnAddUserResponse(statusCode, RoomInfo{});
    }
}

void RoomNetwork::OnSendMessageResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus(ADD_USER_URL);
    if (statusCode == 200) {
        auto body = response->GetBody();
        auto roomData = responseSerializer_->DeserializeResponse(body);
        replyHandler_->OnSendMessageResponse(200, roomData->GetLastMessages());
    } else {
        replyHandler_->OnSendMessageResponse(statusCode, std::vector<Message>{});
    }
}

void RoomNetwork::OnGetMessagesResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus(ADD_USER_URL);
    if (statusCode == 200) {
        auto body = response->GetBody();
        auto roomData = responseSerializer_->DeserializeResponse(body);
        replyHandler_->OnGetMessagesResponse(200, roomData->GetLastMessages());
    } else {
        replyHandler_->OnGetMessagesResponse(statusCode, std::vector<Message>{});
    }
}

void RoomNetwork::OnCreateRoomResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus(ADD_USER_URL);
    if (statusCode == 200) {
        auto body = response->GetBody();
        auto roomData = responseSerializer_->DeserializeResponse(body);
        replyHandler_->OnCreateRoomResponse(200, std::move(roomData));
    } else {
        replyHandler_->OnCreateRoomResponse(statusCode, nullptr);
    }
}
