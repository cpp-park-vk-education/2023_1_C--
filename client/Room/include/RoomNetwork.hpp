#pragma once
#include "IRoomNetwork.hpp"
#include "IRoomReplyHandler.hpp"
#include "INetworkManager.hpp"
#include "ISerializer.hpp"
#include "IDeserializer.hpp"

class RoomNetwork : public IRoomNetwork {
public:

    RoomNetwork();
    void SendMessage(const Message& message) override;
    void CreateRoom(std::string&& name, 
                    std::vector<std::string>&& members) override;
    void GetNewMessage(const int roomID) override;
    void GetRoomMessages(const int roomID) override;
    void AddUser(const int roomID, const std::string& login) override;
    
    void SetNetworkManager(INetworkManagerSPtr networkManager) {
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
    INetworkManagerSPtr networkManager_;
    IRoomReplyHandlerSPtr replyHandler_;
    ISerializerSPtr serializer_;
    IDeserializerSPtr deserializer_;
    Callback createRoomCallback;
    Callback sendMessageCallback;
    Callback getNewMessageCallback;
    Callback getRoomMessagesCallback;
    Callback addUserCallback;
    void OnSendMessageResponse(IResponseUPtr response);
    void OnGetNewMessageResponse(IResponseUPtr response);
    void OnGetRoomMessagesResponse(IResponseUPtr response);
    void OnCreateRoomResponse(IResponseUPtr response);
    void OnAddUserResponse(IResponseUPtr response);
};
