#pragma once
#include "IAccountNetwork.hpp"
#include "INetworkManager.hpp"
#include "IAccountSerializer.hpp"
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
    void Login(const LoginData& data) override;
    void Signup(const SignupData& data) override;
    void UserSetting(const UserSettingData& data) override;
    void Logout(const LogoutData& data) override;
    void OnLoginResponse(IResponseUPtr response);
    void OnSignupResponse(IResponseUPtr response);
    void OnUserSettingResponse(IResponseUPtr response);
    void OnLogoutResponse(IResponseUPtr response);
    
    void SetNetworkManager(INetworkManagerUPtr networkManager) {
        networkManager_ = std::move(networkManager);
    }

    void SetReplyHandler(IAccountReplyHandlerUPtr replyHandler) {
        replyHandler_ = std::move(replyHandler);
    }

    void SetRequestSerializer(IAccountRequestSerializerUPtr serializer) {
        requestSerializer_ = std::move(serializer);
    }

    void SetResponseSerializer(IAccountResponseSerializerUPtr serializer) {
        responseSerializer_ = std::move(serializer);
    }

private:
    INetworkManagerUPtr networkManager_;
    IAccountReplyHandlerUPtr replyHandler_;
    IAccountRequestSerializerUPtr requestSerializer_;
    IAccountResponseSerializerUPtr responseSerializer_;
    Request CreateRequest(const std::string& url, 
                          const Headers& headers);
};
