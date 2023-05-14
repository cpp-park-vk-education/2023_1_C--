#pragma once
#include "AccountData.hpp"
#include <memory>

class IUserInfoUi {
public:
    virtual ~IUserInfoUi() {}
    virtual void ShowUserInfo(const UserInfo& userInfo) = 0;
};

using IUserInfoUiSPtr = std::shared_ptr<IUserInfoUi>;
