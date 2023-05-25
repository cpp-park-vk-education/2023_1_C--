#pragma once
#include "RoomData.hpp"
#include "AccountData.hpp"
#include <vector>

class IMainPage {
public:
    virtual ~IMainPage() {}
    virtual void ShowRooms(const std::vector<RoomInfo>& rooms) = 0;
    virtual void ShowError(const std::string& error) = 0;
};

using IMainPageSPtr = std::shared_ptr<IMainPage>;
