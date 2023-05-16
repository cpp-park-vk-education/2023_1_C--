#pragma once
#include "IDeserializer.hpp"

class Deserializer: public IDeserializer {
public:
    UserData DeserializeRoomData(std::vector<char> byteArray) override;
    RoomData DeserializeCreateRoomResponse(std::vector<char> byteArray) override;
    Message DeserializeMessage(std::vector<char> byteArray) override;
    virtual std::vector<Message> DeserializeRoomMessages(std::vector<char> byteArray);
};
