#pragma once
#include "IDeserializer.hpp"

class Deserializer: public IDeserializer {
public:
    UserData DeserializeUserData(std::vector<char> byteArray) override;
    // RoomData DeserializeRoom(std::vector<char> byteArray) override;
};
