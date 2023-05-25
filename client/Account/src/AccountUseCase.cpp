#include "Errors.hpp"
#include "AccountData.hpp"
#include "AccountUseCase.hpp"

void AccountUseCase::Login(ILoginFormUPtr form) {
    try {
        form->validate();
        network_->Login(form->getLoginData());
    } catch (const FormError& ex) {
        loginPage_->ShowError(ex.what());
    }
}

void AccountUseCase::Signup(ISignupFormUPtr form) {
    try {
        form->validate();
        network_->Signup(form->getSignupData());
    } catch (const FormError& ex) {
        signupPage_->ShowError(ex.what());
    }
}

void AccountUseCase::UserSetting(IUserSettingFormUPtr form) {}
void AccountUseCase::Logout(const std::string& token) {}

void AccountUseCase::OnLoginResponse(const int statusCode, UserData&& userData) {
    if (statusCode != 200) {
        loginPage_->ShowError("Error:" + std::to_string(statusCode) + " status code");
    }
    else {
        userInfo_ = userData.info;
        roomUseCase_->ShowMainPage(std::move(userData));
    }
}

void AccountUseCase::OnSignupResponse(const int statusCode, UserData&& userData) {
    if (statusCode != 200)
        signupPage_->ShowError("Error:" + std::to_string(statusCode) + " status code");
    else {
        userInfo_ = userData.info;
        roomUseCase_->ShowMainPage(std::move(userData));
    }
}

void AccountUseCase::OnUserSettingResponse(const int statusCode, UserData&& userData) {}
void AccountUseCase::OnLogoutResponse(const int statusCode) {}
