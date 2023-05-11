#pragma once
#include <memory>
#include <vector>

struct RoomInfo {};
struct Message {};

class IRoom {
public:
    virtual ~IRoom() {}
    virtual RoomInfo GetRoomInfo() = 0;
    virtual std::vector<Message> GetLastMessages() = 0;
};

using IRoomUPtr = std::unique_ptr<IRoom>;
