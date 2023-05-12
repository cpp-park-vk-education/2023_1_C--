#include "AccountReplyHandler.hpp"

void AccountReplyHandler::OnLoginResponse(unsigned int statusCode, IUserDataUPtr userData) {
    if (statusCode == 200) {
        widgetController_->ShowMainPage();
        roomSwitcher_->ShowMainPage(userData->GetUserRooms(), userData->GetUserInfo());
    } else {
        accountUi_->ShowError("Error:" + std::to_string(statusCode) + " status code");
    }
}

void AccountReplyHandler::OnSignupResponse(unsigned int statusCode, IUserDataUPtr userData) {
    if (statusCode == 200) {
        widgetController_->ShowMainPage();
        roomSwitcher_->ShowMainPage(userData->GetUserRooms(), userData->GetUserInfo());
    } else {
        accountUi_->ShowError("Error:" + std::to_string(statusCode) + " status code");
    }
}

void AccountReplyHandler::OnUserSettingResponse(unsigned int statusCode, IUserDataUPtr userData) {
    if (statusCode == 200) {
        widgetController_->ShowMainPage();
        roomSwitcher_->ShowMainPage(userData->GetUserRooms(), userData->GetUserInfo());
    } else {
        accountUi_->ShowError("Error:" + std::to_string(statusCode) + " status code");
    }
}

void AccountReplyHandler::OnLogoutResponse(unsigned int statusCode) {
    if (statusCode == 200) {
        widgetController_->ShowLoginPage();
    } else {
        accountUi_->ShowError("Error:" + std::to_string(statusCode) + " status code");
    }
}
