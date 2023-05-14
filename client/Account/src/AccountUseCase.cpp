#include "AccountUseCase.hpp"
#include "Errors.hpp"
#include "AccountData.hpp"

void AccountUseCase::Login(ILoginFormUPtr form) {
    try {
        form->validate();
        network_->Login(form->getLoginData());
    } catch (const FormError& ex) {
        accountUi_->ShowError(ex.what());
    }
}

void AccountUseCase::Signup(ISignupFormUPtr form) {
//     try {
//         form->validate();
//         network_->Signup(form->getSignupData());
//     } catch (const FormError& ex) {
//         accountUi_->ShowError(ex.what());
//     }
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