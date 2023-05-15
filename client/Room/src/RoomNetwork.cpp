#include "RoomNetwork.hpp"
#include "Communication.hpp"

const std::string ADD_USER_URL = "/add";
const std::string SEND_MESSAGE_URL = "/send";
const std::string CREATE_ROOM_URL = "/create";
const std::string GET_MESSAGES_URL = "/get";

void RoomNetwork::AddUser(const std::string& login) {}
void RoomNetwork::SendMessage(const Message& message) {}

static QByteArray GetQByteArray(std::vector<char> byteArray) {
    QByteArray qByteArray;
    for (auto byte: byteArray)
        qByteArray.push_back(byte);
    return qByteArray;
}

void RoomNetwork::CreateRoom(const RoomInfo& roomInfo) {
    auto request = CreateRequest(CREATE_ROOM_URL);
    auto byteArray = serializer_->SerializeRoomInfo(roomInfo);
    Callback callback (
        [this](IResponseUPtr response){
           return this->OnCreateRoomResponse(std::move(response)); 
        }
    ); 
    networkManager_->Post(request, GetQByteArray(byteArray), callback);
}

void RoomNetwork::GetMessages(const size_t messageId) {}
void RoomNetwork::OnAddUserResponse(IResponseUPtr response) {}
void RoomNetwork::OnSendMessageResponse(IResponseUPtr response) {}
void RoomNetwork::OnGetMessagesResponse(IResponseUPtr response) {}

void RoomNetwork::OnCreateRoomResponse(IResponseUPtr response) {
    auto statusCode = response->GetStatus();
    if (statusCode == 200) {
        RoomData data = deserializer_->DeserializeCreateRoomResponse(response->GetBody());
        replyHandler_->OnCreateRoomResponse(200, data);
    } else {
        replyHandler_->OnCreateRoomResponse(statusCode, RoomData{});
    }
}
