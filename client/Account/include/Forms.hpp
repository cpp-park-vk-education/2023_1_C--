#pragma once
#include <string>
#include <unordered_map>
#include "IForms.hpp"

class LoginForm : public ILoginForm {
public:
    LoginForm() {}
    LoginForm(const std::string& login, const std::string& password)
        : login_(login), password_(password) {}

    void validate() const override;

    LoginData getLoginData() const;

private:
    std::string login_;
    std::string password_;
};

class SignupForm : public ISignupForm {
public:
    SignupForm() {}
    SignupForm(const std::string& login,
               const std::string& nickname,
               const std::string& password,
               const std::string& repeatedPassword)
        : login_(login), nickname_(nickname), 
          password_(password), repeatedPassword_(repeatedPassword)  {}

    void validate() const override;

    SignupData getSignupData() const override;

    void SetFirstname(const std::string& firstname) {
        firstname_ = firstname;
    }

    void SetLastname(const std::string& lastname) {
        lastname_ = lastname;
    }

private:
    std::string login_;
    std::string password_;
    std::string repeatedPassword_;
    std::string firstname_;
    std::string lastname_;
    std::string nickname_;
};
