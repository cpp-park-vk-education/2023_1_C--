#pragma once
#include "UserData.hpp"
#include "IAccountReplyHandler.hpp"
#include "IAccountUi.hpp"
#include "IWidgetController.hpp"
#include "IRoomSwitcher.hpp"

class AccountReplyHandler : public IAccountReplyHandler {
public:
    void OnLoginResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    void OnSignupResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    void OnUserSettingResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    void OnLogoutResponse(unsigned int statusCode) override;

    void SetAccountUi(IAccountUiUPtr accountUi) {
        accountUi_ = std::move(accountUi);
    }
    void SetWidgetController(IWidgetControllerUPtr widgetController) {
        widgetController_ = std::move(widgetController);
    }
    void SetRoomSwitcher(IRoomSwitcherUPtr roomSwitcher) {
        roomSwitcher_ = std::move(roomSwitcher);
    }

private:
    IAccountUiUPtr accountUi_;
    IWidgetControllerUPtr widgetController_;
    IRoomSwitcherUPtr roomSwitcher_;
};