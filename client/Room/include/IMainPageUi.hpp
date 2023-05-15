#pragma once
#include "RoomData.hpp"
#include <vector>

class IMainPageUi {
public:
    virtual ~IMainPageUi() {}
    virtual void ShowMainPage(std::vector<RoomData> rooms) = 0;
    virtual void ShowRoomSearchPage() = 0;
    virtual void ShowRoomCreationPage() = 0;
};

using IMainPageUiSPtr = std::shared_ptr<IMainPageUi>;
