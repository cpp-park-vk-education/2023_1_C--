#pragma once
#include "IRoomNetwork.hpp"
#include "IRoomReplyHandler.hpp"
#include "INetworkManager.hpp"
#include "IRoomSerializer.hpp"

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
    
    void SetNetworkManager(INetworkManagerSPtr networkManager) {
        networkManager_ = networkManager;
    }

    void SetReplyHandler(IRoomReplyHandlerSPtr replyHandler) {
        replyHandler_ = replyHandler;
    }

    void SetRequestSerializer(IRoomRequestSerializerSPtr serializer) {
        requestSerializer_ = serializer;
    }

    void SetResponseSerializer(IRoomResponseDeserializerSPtr serializer) {
        responseSerializer_ = serializer;
    }

private:
    INetworkManagerSPtr networkManager_;
    IRoomReplyHandlerSPtr replyHandler_;
    IRoomRequestSerializerSPtr requestSerializer_;
    IRoomResponseDeserializerSPtr responseSerializer_;
};
