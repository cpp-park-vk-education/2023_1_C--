#pragma once
#include "IForms.hpp"
#include "IAccountUi.hpp"
#include "IAccountUseCase.hpp"
#include "IAccountNetwork.hpp"

class AccountUseCase : public IAccountUseCase {
public:
    void Login(ILoginFormUPtr form) override;
    void Signup(ISignupFormUPtr form) override;
    void UserSetting(IUserSettingFormUPtr form) override;
    void Logout(const std::string& token) override;

    void SetNetwork(IAccountNetworkSPtr network) {
        network_ = network;
    }

    void SetAccountUi(IAccountUiSPtr accountUi) {
        accountUi_ = std::move(accountUi);
    }
    
    
private:
    IAccountUiSPtr accountUi_;
    IAccountNetworkSPtr network_;
};
