#include <regex>
#include "Forms.hpp"
#include "Errors.hpp"

const std::regex LOGIN_PATTERN("^[a-zA-Z0-9](_(?!_)|[a-zA-Z0-9]){3,16}[a-zA-Z0-9]$"); 
const std::regex PASSWORD_PATTERN("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=\\S+$).{4,16}");
const std::regex NICKNAME_PATTERN("([a-zA-Z0-9]){3,16}");
const std::regex NAME_PATTERN("^[a-zA-Z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");

void LoginForm::validate() const {
    validateLogin();
    validatePassword();
}
void LoginForm::validateLogin() const {
    if (!std::regex_match(login_, LOGIN_PATTERN)){
        throw FormError{"The login must be between 3 and 16 characters \
                            long and cannot contain spaces or special characters"};
    }
}

void LoginForm::validatePassword() const {
    if (!std::regex_match(password_, PASSWORD_PATTERN)){
        throw FormError{"The password must be between 4 and 16 characters \
                        long, consist of uppercase, lowercase letters and numbers"};
    }
}

TextData LoginForm::getTextData() const {
    return TextData {
        {"login", login_},
        {"password", password_} 
    };
}

void SignupForm::validate() const {
    validateLogin();
    validatePassword();
    validateNickname();
    validateName();
    if (password_ != repeatedPassword_) {
        throw FormError{"Passwords don't match"};
    }
}

void SignupForm::validateNickname() const {
    if (!std::regex_match(nickname_, NICKNAME_PATTERN)){
        throw FormError{"The nickname must be between 3 and 16 characters long"};
    }
} 

void SignupForm::validateName() const {
    if (firstname_.empty()) {
        return;
    }
    if (!std::regex_match(firstname_, NAME_PATTERN)){
        throw FormError{"Incorrect firstname"};
    }
    if (lastname_.empty()) {
        return;
    }
    if (!std::regex_match(lastname_, NAME_PATTERN)){
        throw FormError{"Incorrect lastname"};
    }
}

TextData SignupForm::getTextData() const {
    return TextData {
        {"login", login_},
        {"nickname", nickname_},
        {"firstname", firstname_},
        {"lastname", lastname_},
        {"password", password_} 
    };    
}
