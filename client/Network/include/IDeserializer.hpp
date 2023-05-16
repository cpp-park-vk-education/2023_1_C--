#pragma once
#include <vector>
#include <memory>
#include "AccountData.hpp"

class IDeserializer {
public:
    virtual ~IDeserializer() {}
    virtual UserData DeserializeRoomData(std::vector<char> byteArray)  = 0;
    virtual RoomData DeserializeCreateRoomResponse(std::vector<char> byteArray) = 0;
    virtual Message DeserializeMessage(std::vector<char> byteArray) = 0;
    virtual std::vector<Message> DeserializeRoomMessages(std::vector<char> byteArray) = 0;
};

using IDeserializerSPtr = std::shared_ptr<IDeserializer>;
