#pragma once
#include <string>
#include <vector>
#include "UserInfo.hpp"

struct RoomInfo {
    RoomInfo() {}
    ~RoomInfo() {}


    RoomInfo(const RoomInfo& other)
        : id(other.id), name(other.name), members(other.members) {}

    RoomInfo& operator=(const RoomInfo& other) {

        if (this == &other)
            return *this;

        id = other.id;
        name = other.name;
        members = other.members;
        return *this;
    }
    
    int id;
    std::string name;
    std::vector<UserInfo> members;
};