#pragma once
#include "IForms.hpp"
#include "IAccountUi.hpp"
#include "IRoomSwitcher.hpp"
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
    void OnLoginResponse(const int statusCode, UserData userData) override;
    void OnSignupResponse(const int statusCode, UserData userData) override;
    void OnUserSettingResponse(const int statusCode, UserData userData) override;
    void OnLogoutResponse(const int statusCode) override;

    void SetUi(IAccountUi* ui) {
        ui_ = ui;
    }

    void SetNetwork(IAccountNetworkSPtr network) {
        network_ = network;
    }

    void SetRoomSwitcher(IRoomSwitcherSPtr switcher) {
        switcher_ = switcher;
    }
    
private:
    IAccountUi* ui_;
    IAccountNetworkSPtr network_;
    IRoomSwitcherSPtr switcher_;
};
