#pragma once
#include "IAccountNetwork.hpp"
#include "INetworkManager.hpp"
#include "IAccountReplyHandler.hpp"
#include "IClientSerializer.hpp"

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
    
    void SetNetworkManager(INetworkManagerSPtr networkManager) {
        networkManager_ = networkManager;
    }

    void SetReplyHandler(IAccountReplyHandlerSPtr replyHandler) {
        replyHandler_ = replyHandler;
    }

    void SetRequestSerializer(IAccountRequestSerializerSPtr serializer) {
        requestSerializer_ = std::move(serializer);
    }

    void SetResponseSerializer(IAccountResponseDeserializerSPtr serializer) {
        responseSerializer_ = std::move(serializer);
    }

private:
    INetworkManagerSPtr networkManager_;
    IAccountReplyHandlerSPtr replyHandler_;
    IAccountRequestSerializerSPtr requestSerializer_;
    IAccountResponseDeserializerSPtr responseSerializer_;
};
