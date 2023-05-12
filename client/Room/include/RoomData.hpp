#pragma once
#include <memory>
#include <string>
#include <vector>

struct RoomInfo {
    std::vector<std::string> members;
    std::string name;
};

struct Message {
    size_t id;
    std::string content;
    std::string author;
    std::string sendingData;
};

class IRoom {
public:
    virtual ~IRoom() {}
    virtual RoomInfo GetRoomInfo() = 0;
    virtual std::vector<Message> GetLastMessages() = 0;
};

using IRoomUPtr = std::unique_ptr<IRoom>;
