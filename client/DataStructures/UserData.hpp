#pragma once
#include <vector>
#include "UserInfo.hpp"
#include "RoomInfo.hpp"

struct UserData {
    UserInfo info;
    std::vector<RoomInfo> rooms;
};
