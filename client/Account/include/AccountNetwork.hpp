#pragma once
#include "IAccountNetwork.hpp"
#include "IAccountReplyHandler.hpp"
#include "ISerializer.hpp"
#include "IDeserializer.hpp"
#include "INetworkManager.hpp"

class AccountNetwork : public IAccountNetwork {
public:
    AccountNetwork();
    void Login(const LoginData& data) override;
    void Signup(const SignupData& data) override;
    void UserSetting(const UserSettingData& data) override;
    void Logout(const LogoutData& data) override;
    void OnLoginResponse(IResponseUPtr response);
    void OnSignupResponse(IResponseUPtr response);
    void OnUserSettingResponse(IResponseUPtr response);
    void OnLogoutResponse(IResponseUPtr response);
    
    void SetNetworkManager(INetworkManagerSPtr networkManager) {
        networkManager_ = networkManager;
    }

    void SetReplyHandler(IAccountReplyHandlerSPtr replyHandler) {
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
    IAccountReplyHandlerSPtr replyHandler_;
    ISerializerSPtr serializer_;
    IDeserializerSPtr deserializer_;
    Callback loginCallback;
    Callback signupCallback;
};
