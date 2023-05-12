#pragma once
#include "UserData.hpp"
#include <memory>

class IUserInfoUi {
public:
    virtual ~IUserInfoUi() {}
    virtual void ShowUserInfo(const UserInfo& userInfo) = 0;
};

using IUserInfoUiUPtr = std::unique_ptr<IUserInfoUi>;
