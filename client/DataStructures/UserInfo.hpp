#pragma once
#include <string>

struct UserInfo {

    UserInfo() {}
    ~UserInfo() {}

    UserInfo(const UserInfo& other)
        : login(other.login), nickname(other.nickname),
        firstName(other.firstName), lastName(other.lastName) {}

    UserInfo& operator=(const UserInfo& other) {
        login = other.login;
        nickname = other.nickname;
        firstName = other.firstName; 
        lastName = other.lastName;
        return *this;
    }

    std::string login;
    std::string nickname;
    std::string firstName;
    std::string lastName;
};
