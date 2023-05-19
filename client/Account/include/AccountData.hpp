#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "RoomData.hpp"

struct UserInfo {
    std::string login;
    std::string nickname;
    std::string firstName;
    std::string lastName;
};

struct UserData {
    UserInfo info;
    std::vector<RoomInfo> rooms;
};

struct LoginData {
    std::string login;
    std::string password;
};

struct SignupData {
    std::string login;
    std::string password;
    std::string nickname;
    std::string firstName;
    std::string lastName;
};

struct UserSettingData {
    std::string token;
    std::string nickname;
    std::string firstname;
    std::string lastname;
};

struct LogoutData {
    std::string token;
    std::string login;
};
