#pragma once
#include <memory>
#include "UserData.hpp"

struct UserInfo;

class IRoomUi {
public:
    virtual ~IRoomUi() {}
    virtual void ShowUserInfo(UserInfo roomsList) = 0;
};

using IRoomUiUPtr = std::unique_ptr<IRoomUi>;
