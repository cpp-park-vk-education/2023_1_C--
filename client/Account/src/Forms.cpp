#include <regex>
#include "Forms.hpp"
#include "Errors.hpp"

const std::regex LOGIN_PATTERN("^[a-zA-Z0-9](_(?!_)|[a-zA-Z0-9]){1,16}[a-zA-Z0-9]$");
const std::regex PASSWORD_PATTERN("^([a-zA-Z0-9@*#]{4,16})$");
const std::regex NICKNAME_PATTERN("([a-zA-Z0-9]){3,16}");
const std::regex NAME_PATTERN("^[a-zA-Z]+(([',. -][a-zA-Z ])?[a-zA-Z]*)*$");

static void validateLogin(const std::string& login) {
    if (!std::regex_match(login, LOGIN_PATTERN)){
        throw FormError{"The login must be between 3 and 16 characters long and cannot contain spaces or special characters"};
    }
}

static void validatePassword(const std::string& password) {
    if (!std::regex_match(password, PASSWORD_PATTERN)){
        throw FormError{"The password must be between 4 and 16 characters long"};
    }
}

static void validateNickname(const std::string& nickname) {
    if (!std::regex_match(nickname, NICKNAME_PATTERN)){
        throw FormError{"The nickname must be between 3 and 16 characters long"};
    }
} 

static void validateName(const std::string& firstname,
                         const std::string& lastname) {
    if (firstname.empty() && lastname.empty()) {
        return;
    }
    if (!std::regex_match(firstname, NAME_PATTERN)){
        throw FormError{"Incorrect firstname"};
    }
    if (lastname.empty()) {
        return;
    }
    if (!std::regex_match(lastname, NAME_PATTERN)){
        throw FormError{"Incorrect lastname"};
    }
}

void LoginForm::validate() const {
    validateLogin(login_);
    validatePassword(password_);
}

LoginData LoginForm::getLoginData() const {
    LoginData loginData{};
    loginData.login = login_;
    loginData.password = password_;
    return loginData;
}

void SignupForm::validate() const {
    validateLogin(login_);
    validatePassword(password_);
    validateNickname(nickname_);
    validateName(firstname_, lastname_);
    if (password_ != repeatedPassword_) {
        throw FormError{"Passwords don't match"};
    }
}

SignupData SignupForm::getSignupData() const {
    SignupData signupData{};
    signupData.login = login_;
    signupData.nickname = nickname_;
    signupData.password = password_;
    signupData.firstName = firstname_;
    signupData.lastName = firstname_;
    return signupData;
}
