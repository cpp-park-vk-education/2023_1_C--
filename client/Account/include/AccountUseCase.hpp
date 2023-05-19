#pragma once
#include "IForms.hpp"
#include "ILoginPage.hpp"
#include "ISignupPage.hpp"
#include "IRoomUseCase.hpp"
#include "IMainPage.hpp"
#include "IAccountUseCase.hpp"
#include "IAccountReplyHandler.hpp"
#include "IAccountNetwork.hpp"

class AccountUseCase : public IAccountUseCase,
                       public IAccountReplyHandler  {
public:
    void Login(ILoginFormUPtr form) override;
    void Signup(ISignupFormUPtr form) override;
    void UserSetting(IUserSettingFormUPtr form) override;
    void Logout(const std::string& token) override;
    void OnLoginResponse(const int statusCode, UserData&& userData) override;
    void OnSignupResponse(const int statusCode, UserData&& userData) override;
    void OnUserSettingResponse(const int statusCode, UserData&& userData) override;
    void OnLogoutResponse(const int statusCode) override;

    void SetLoginPage(ILoginPage* loginPage) {
        loginPage_ = loginPage;
    }

    void SetSignupPage(ISignupPage* signupPage) {
        signupPage_ = signupPage;
    }

    void SetNetwork(IAccountNetworkSPtr network) {
        network_ = network;
    }

    void SetRoomUseCase(IRoomUseCaseSPtr roomUseCase) {
        roomUseCase_ = roomUseCase;
    }
    
private:
    ILoginPage* loginPage_;
    ISignupPage* signupPage_;
    IAccountNetworkSPtr network_;
    IRoomUseCaseSPtr roomUseCase_;
    UserInfo userInfo_;
};
