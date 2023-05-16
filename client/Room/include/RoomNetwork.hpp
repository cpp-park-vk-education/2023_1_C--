#pragma once
#include "IRoomNetwork.hpp"
#include "IRoomReplyHandler.hpp"
#include "NetworkManager.hpp"
#include "ISerializer.hpp"
#include "IDeserializer.hpp"

class RoomNetwork : public IRoomNetwork {
public:
    void SendMessage(const Message& message) override;
    void CreateRoom(const RoomInfo& roomInfo) override;
    void GetNewMessage(const int roomID) override;
    void GetRoomMessages(const int roomID) override;
    
    void SetNetworkManager(NetworkManager* networkManager) {
        networkManager_ = networkManager;
    }

    void SetReplyHandler(IRoomReplyHandlerSPtr replyHandler) {
        replyHandler_ = replyHandler;
    }

    void SetRequestSerializer(ISerializerSPtr serializer) {
        serializer_ = serializer;
    }

    void SetResponseSerializer(IDeserializerSPtr serializer) {
        deserializer_ = serializer;
    }

private:
    NetworkManager* networkManager_;
    IRoomReplyHandlerSPtr replyHandler_;
    ISerializerSPtr serializer_;
    IDeserializerSPtr deserializer_;
    void OnSendMessageResponse(IResponseUPtr response);
    void OnGetNewMessageResponse(IResponseUPtr response);
    void OnGetRoomMessagesResponse(IResponseUPtr response);
    void OnCreateRoomResponse(IResponseUPtr response);
};
