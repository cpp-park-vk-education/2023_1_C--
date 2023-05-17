#include "Errors.hpp"
#include "AccountUseCase.hpp"
#include "AccountData.hpp"

void AccountUseCase::Login(ILoginFormUPtr form) {
    try {
        form->validate();
        network_->Login(form->getLoginData());
    } catch (const FormError& ex) {
        ui_->ShowError(ex.what());
    }
}

void AccountUseCase::Signup(ISignupFormUPtr form) {
    try {
        form->validate();
        network_->Signup(form->getSignupData());
    } catch (const FormError& ex) {
        ui_->ShowError(ex.what());
    }
}

void AccountUseCase::UserSetting(IUserSettingFormUPtr form) {
//     try {
//         form->validate();
//         network_->UserSetting(form->getUserSettingData());
//     } catch (const FormError& ex) {
//         accountUi_->ShowError(ex.what());
//     }
}

void AccountUseCase::Logout(const std::string& token) {
//     LogoutData logoutData;
//     logoutData.token = token;
//     network_->Logout(logoutData);
}

void AccountUseCase::OnLoginResponse(const int statusCode, UserData userData) {
    if (statusCode != 200)
        ui_->ShowError("Error:" + std::to_string(statusCode) + " status code");
    else
        switcher_->ShowMainPage(userData.rooms, userData.info);
}

void AccountUseCase::OnSignupResponse(const int statusCode, UserData userData) {}
void AccountUseCase::OnUserSettingResponse(const int statusCode, UserData userData) {}
void AccountUseCase::OnLogoutResponse(const int statusCode) {}
