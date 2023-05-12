#pragma once
#include "UserData.hpp"
#include "IAccountReplyHandler.hpp"
#include "IAccountUi.hpp"
#include "IWidgetController.hpp"
#include "IAccountSwitcher.hpp"
#include "IRoomSwitcher.hpp"

class AccountReplyHandler : public IAccountReplyHandler {
public:
    void OnLoginResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    void OnSignupResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    void OnUserSettingResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    void OnLogoutResponse(unsigned int statusCode) override;

    void SetAccountUi(IAccountUiSPtr accountUi) {
        accountUi_ = accountUi;
    }
    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

private:
    IAccountUiSPtr accountUi_;
    IAccountSwitcherSPtr accountSwitcher_;
    IRoomSwitcherSPtr roomSwitcher_;
};
