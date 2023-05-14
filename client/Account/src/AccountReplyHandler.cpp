#include "AccountReplyHandler.hpp"

void AccountReplyHandler::OnLoginResponse(const int statusCode, UserData userData) {
    if (statusCode != 200)
        accountUi_->ShowError("Error:" + std::to_string(statusCode) + " status code");
    else
        roomSwitcher_->ShowMainPage(userData.rooms, userData.info);
}

void AccountReplyHandler::OnSignupResponse(const int statusCode, UserData userData) {}
void AccountReplyHandler::OnUserSettingResponse(const int statusCode, UserData userData) {}
void AccountReplyHandler::OnLogoutResponse(const int statusCode) {}
