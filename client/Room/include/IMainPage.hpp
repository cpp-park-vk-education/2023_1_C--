#pragma once
#include "RoomData.hpp"
#include "AccountData.hpp"
#include <vector>

using Rooms = std::unordered_map<int, RoomInfo>;

class IMainPage {
public:
    virtual ~IMainPage() {}
    virtual void ShowRooms(const Rooms& rooms) = 0;
    virtual void ShowError(const std::string& error) = 0;
};

using IMainPageSPtr = std::shared_ptr<IMainPage>;
