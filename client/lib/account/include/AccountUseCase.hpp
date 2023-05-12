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

    void SetNetwork(IAccountNetworkUPtr network) {
        network_ = std::move(network);
    }

    void SetAccountUi(IAccountUiUPtr accountUi) {
        accountUi_ = std::move(accountUi);
    }
    
    
private:
    IAccountUiUPtr accountUi_;
    IAccountNetworkUPtr network_;
};
