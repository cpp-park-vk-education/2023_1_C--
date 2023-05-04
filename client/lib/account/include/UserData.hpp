#pragma once
#include "RoomData.hpp"
#include <string>
#include <vector>
#include <memory>

struct UserInfo {
    std::string login;
    std::string nickname;
    std::string firstName;
    std::string lastName;
};

class IUserData {
public:
    ~IUserData() {};
    virtual std::string GetToken() = 0; 
    virtual UserInfo GetUserInfo() = 0;
    virtual std::vector<IRoomUPtr> GetUserRooms() = 0;
};

using IUserDataUPtr = std::unique_ptr<IUserData>;
