#pragma once
#include "UserData.hpp"
#include "IAccountReplyHandler.hpp"
#include "IAccountUi.hpp"
#include "IWidgetController.hpp"
#include "IRoomPage.hpp"

class AccountReplyHandler : public IAccountReplyHandler {
public:

    void OnLoginResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    void OnSignupResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    void OnUserSettingResponse(unsigned int statusCode, IUserDataUPtr userData) override;
    // void OnLogOutResponse() override;

    void SetAccountUi(IAccountUiUPtr accountUi) {
        accountUi_ = std::move(accountUi);
    }
    void SetWidgetController(IWidgetControllerUPtr widgetController) {
        widgetController_ = std::move(widgetController);
    }
    void SetRoomUi(IRoomUiUPtr roomUi) {
        roomUi_ = std::move(roomUi);
    }

private:
    IAccountUiUPtr accountUi_;
    IWidgetControllerUPtr widgetController_;
    IRoomUiUPtr roomUi_;
};
