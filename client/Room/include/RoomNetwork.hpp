#pragma once
#include "IRoomNetwork.hpp"
#include "IRoomReplyHandler.hpp"
#include "NetworkManager.hpp"
#include "ISerializer.hpp"
#include "IDeserializer.hpp"

using Headers = std::unordered_map<std::string, std::string>;


class RoomNetwork : public IRoomNetwork {
public:
    void AddUser(const std::string& login) override;
    void SendMessage(const Message& message) override;
    void CreateRoom(const RoomInfo& roomInfo) override;
    void GetMessages(const size_t messageId) override;
    void OnAddUserResponse(IResponseUPtr response);
    void OnSendMessageResponse(IResponseUPtr response);
    void OnGetMessagesResponse(IResponseUPtr response);
    void OnCreateRoomResponse(IResponseUPtr response);
    
    void SetNetworkManager(NetworkManager* networkManager) {
        networkManager_ = networkManager;
    }

    void SetReplyHandler(IRoomReplyHandlerSPtr replyHandler) {
        replyHandler_ = replyHandler;
    }

    void SetRequestSerializer(ISerializerSPtr serializer) {
        requestSerializer_ = serializer;
    }

    void SetResponseSerializer(IDeserializerSPtr serializer) {
        responseSerializer_ = serializer;
    }

private:
    NetworkManager* networkManager_;
    IRoomReplyHandlerSPtr replyHandler_;
    ISerializerSPtr requestSerializer_;
    IDeserializerSPtr responseSerializer_;
};
