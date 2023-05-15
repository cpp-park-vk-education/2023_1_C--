#pragma once
#include <vector>
#include <memory>
#include "AccountData.hpp"

class IDeserializer {
public:
    virtual ~IDeserializer() {}
    virtual UserData DeserializeLoginResponse(std::vector<char> byteArray)  = 0;
    virtual RoomData DeserializeCreateRoomResponse(std::vector<char> byteArray) = 0;
};

using IDeserializerSPtr = std::shared_ptr<IDeserializer>;
