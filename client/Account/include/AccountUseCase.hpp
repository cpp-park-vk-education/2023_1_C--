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
    void OnLoginResponse(UserData&& userData) override;
    void OnLoginResponse(std::string&& userData) override;
    void OnSignupResponse(UserData&& userData) override;
    void OnSignupResponse(std::string&& error) override;

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
