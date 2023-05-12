#pragma once
#include "IRoomNetwork.hpp"
#include "IRoomReplyHandler.hpp"
#include "INetworkManager.hpp"
#include "IRoomSerializer.hpp"

using Headers = std::unordered_map<std::string, std::string>;

class Request : public IRequest {
public:
    void SetHeader(const std::string& key, const std::string& value) override {
        headers_.insert({key, value});
    }
    void SetURL(const std::string& url) override { url_ = url; }
    void SetBody(std::vector<char> body) override {
        body = std::move(body_);
    }

private:
    std::string url_;
    std::unordered_map<std::string, std::string> headers_;
    std::vector<char> body_;
};


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
    
    void SetNetworkManager(INetworkManagerUPtr networkManager) {
        networkManager_ = std::move(networkManager);
    }

    void SetReplyHandler(IRoomReplyHandlerUPtr replyHandler) {
        replyHandler_ = std::move(replyHandler);
    }

    void SetRequestSerializer(IRoomRequestSerializerUPtr serializer) {
        requestSerializer_ = std::move(serializer);
    }

    void SetResponseSerializer(IRoomResponseDeserializerUPtr serializer) {
        responseSerializer_ = std::move(serializer);
    }

private:
    INetworkManagerUPtr networkManager_;
    IRoomReplyHandlerUPtr replyHandler_;
    IRoomRequestSerializerUPtr requestSerializer_;
    IRoomResponseDeserializerUPtr responseSerializer_;
    Request CreateRequest(const std::string& url, 
                          const Headers& headers);
};

