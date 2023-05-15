#pragma once
#include "IDeserializer.hpp"

class Deserializer: public IDeserializer {
public:
    UserData DeserializeLoginResponse(std::vector<char> byteArray) override;
    RoomData DeserializeCreateRoomResponse(std::vector<char> byteArray) override;
    // RoomData DeserializeRoom(std::vector<char> byteArray) override;
};
