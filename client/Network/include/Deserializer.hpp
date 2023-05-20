#pragma once
#include "IDeserializer.hpp"

class Deserializer: public IDeserializer {
public:
    UserData DeserializeUserData(std::vector<char> byteArray) override;
    UserInfo DeserializeUserInfo(std::vector<char> byteArray)  override;
    RoomInfo DeserializeCreateRoomResponse(std::vector<char> byteArray) override;
    Message DeserializeMessage(std::vector<char> byteArray) override;
    virtual std::vector<Message> DeserializeRoomMessages(std::vector<char> byteArray);
};
