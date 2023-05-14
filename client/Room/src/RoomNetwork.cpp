#include "RoomNetwork.hpp"
#include "Communication.hpp"

const std::string ADD_USER_URL = "/add";
const std::string SEND_MESSAGE_URL = "/send";
const std::string CREATE_ROOM_URL = "/create";
const std::string GET_MESSAGES_URL = "/get";

void RoomNetwork::AddUser(const std::string& login) {}
void RoomNetwork::SendMessage(const Message& message) {}
void RoomNetwork::CreateRoom(const RoomInfo& roomInfo) {}
void RoomNetwork::GetMessages(const size_t messageId) {}


void RoomNetwork::OnAddUserResponse(IResponseUPtr response) {}
void RoomNetwork::OnSendMessageResponse(IResponseUPtr response) {}
void RoomNetwork::OnGetMessagesResponse(IResponseUPtr response) {}
void RoomNetwork::OnCreateRoomResponse(IResponseUPtr response) {}
