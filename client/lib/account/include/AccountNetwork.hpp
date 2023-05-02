#pragma once
#include "IAccountNetwork.hpp"
#include "INetworkManager.hpp"
#include "ITextSerializer.hpp"
#include "IAccountReplyHandler.hpp"

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


class AccountNetwork : public IAccountNetwork {
public:
    void Login(const TextData& textData) override;
    void Signup(const TextData& textData) override;
    void UserSetting(const TextData& textData) override;
    void Logout() override;
    void OnLoginResponse(IResponseUPtr response);
    void OnSignupResponse(IResponseUPtr response);
    void OnUserSettingResponse(IResponseUPtr response);
    
    void SetNetworkManager(INetworkManagerUPtr networkManager) {
        networkManager_ = std::move(networkManager);
    }

    void SetReplyHandler(IAccountReplyHandlerUPtr replyHandler) {
        replyHandler_ = std::move(replyHandler);
    }

    void SetSerializer(ITextSerializerUPtr serializer) {
        serializer_ = std::move(serializer);
    }

private:
    INetworkManagerUPtr networkManager_;
    IAccountReplyHandlerUPtr replyHandler_;
    ITextSerializerUPtr serializer_;
    Request CreateRequest(const std::string& url, 
                          const Headers& headers);
};
