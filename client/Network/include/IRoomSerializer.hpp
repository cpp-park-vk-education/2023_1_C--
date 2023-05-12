#pragma once
#include <vector>
#include <memory>
#include <string>
#include "RoomData.hpp"

class IRoomRequestSerializer {
public:
    virtual ~IRoomRequestSerializer() {}
    virtual std::vector<char> SerializeString(const std::string& data) = 0;
    virtual std::vector<char> SerializeMessage(const Message& data) = 0;
    virtual std::vector<char> SerializeRoomInfo(const RoomInfo& data) = 0;
};

class IRoomResponseDeserializer {
public:
    virtual ~IRoomResponseDeserializer() {}
    virtual IRoomUPtr DeserializeResponse(const std::vector<char>& data) = 0;
};

using IRoomRequestSerializerSPtr = std::shared_ptr<IRoomRequestSerializer>;
using IRoomResponseDeserializerSPtr = std::shared_ptr<IRoomResponseDeserializer>;
