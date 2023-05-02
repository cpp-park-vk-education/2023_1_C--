#include "AccountUseCase.hpp"
#include "Errors.hpp"

void AccountUseCase::Login(IFormUPtr form) {
    try {
        form->validate();
        network_->Login(form->getTextData());
    } catch (const FormError& ex) {
        accountUi_->ShowError(ex.what());
    }
}

void AccountUseCase::Signup(IFormUPtr form) {
    try {
        form->validate();
        network_->Signup(form->getTextData());
    } catch (const FormError& ex) {
        accountUi_->ShowError(ex.what());
    }
}

void AccountUseCase::UserSetting(IFormUPtr form) {
    try {
        form->validate();
        network_->UserSetting(form->getTextData());
    } catch (const FormError& ex) {
        accountUi_->ShowError(ex.what());
    }
}

void AccountUseCase::Logout() {
    network_->Logout();
}