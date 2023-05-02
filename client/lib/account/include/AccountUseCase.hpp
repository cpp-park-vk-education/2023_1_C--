#pragma once
#include "Forms.hpp"
#include "IAccountUi.hpp"
#include "IAccountUseCase.hpp"
#include "IAccountNetwork.hpp"

class AccountUseCase : public IAccountUseCase {
public:
    void Login(IFormUPtr form) override;
    void Signup(IFormUPtr form) override;
    void UserSetting(IFormUPtr form) override;
    void Logout() override;

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
