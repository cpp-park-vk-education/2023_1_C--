#pragma once
#include "AccountData.hpp"
#include "IAccountReplyHandler.hpp"
#include "IAccountUi.hpp"
#include "IWidgetController.hpp"
#include "IAccountSwitcher.hpp"
#include "IRoomSwitcher.hpp"

class AccountReplyHandler : public IAccountReplyHandler {
public:
    void OnLoginResponse(const int statusCode, UserData userData) override;
    void OnSignupResponse(const int statusCode, UserData userData) override;
    void OnUserSettingResponse(const int statusCode, UserData userData) override;
    void OnLogoutResponse(const int statusCode) override;

    void SetAccountUi(IAccountUi* accountUi) {
        accountUi_ = accountUi;
    }
    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

private:
    IAccountUi* accountUi_;
    IAccountSwitcherSPtr accountSwitcher_;
    IRoomSwitcherSPtr roomSwitcher_;
};
