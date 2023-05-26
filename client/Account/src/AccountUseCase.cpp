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

void AccountUseCase::OnLoginResponse(UserData&& userData) {
    userInfo_ = userData.info;
    roomUseCase_->ShowMainPage(std::move(userData));
}

void AccountUseCase::OnLoginResponse(std::string&& error) {
    loginPage_->ShowError(error);
}

void AccountUseCase::OnSignupResponse(UserData&& userData) {
    userInfo_ = userData.info;
    roomUseCase_->ShowMainPage(std::move(userData));
}

void AccountUseCase::OnSignupResponse(std::string&& error) {
    signupPage_->ShowError(error);
}
