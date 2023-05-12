#pragma once
#include "RoomData.hpp"
#include <vector>

class IMainPageUi {
public:
    virtual ~IMainPageUi() {}
    virtual void ShowMainPage(const std::vector<IRoomUPtr>& rooms) = 0;
};

using IMainPageUiUPtr = std::unique_ptr<IMainPageUi>;
