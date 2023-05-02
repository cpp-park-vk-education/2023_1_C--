#pragma once
#include <string>
#include <memory>
#include <unordered_map>

using TextData = std::unordered_map<std::string, std::string>;

class IForm {
public:
    virtual ~IForm() {}
    virtual void validate() const = 0;
    virtual TextData getTextData() const = 0;
};

using IFormUPtr = std::unique_ptr<IForm>;

class LoginForm : public IForm {
public:
    LoginForm() {}
    LoginForm(const std::string& login, const std::string& password)
        : login_(login), password_(password) {}

    TextData getTextData() const override;

    void validate() const override;

protected:
    std::string login_;
    std::string password_;
    void validateLogin() const;
    void validatePassword() const;
};


class SignupForm : public LoginForm {
public:
    SignupForm(const std::string login, const std::string& password)
        : LoginForm(login, password) {}

    void SetFirstname(const std::string& firstname) {
        firstname_ = firstname;
    }

    void SetLastname(const std::string& lastname) {
        lastname_ = lastname;
    }

    void SetNickname(const std::string& nickname) {
        nickname_ = nickname;
    }

    void SetRepeatedPassword(const std::string& repeatedPassword) {
        repeatedPassword_ = repeatedPassword;
    }

    TextData getTextData() const;

    void validate() const;

protected:
    std::string firstname_;
    std::string lastname_;
    std::string nickname_;
    std::string repeatedPassword_;
    void validateNickname() const;
    void validateName() const;
};

class UserSettingForm : public SignupForm {
public:
    UserSettingForm(const std::string& login, const std::string& password) 
        : SignupForm(login, password) {}
};

