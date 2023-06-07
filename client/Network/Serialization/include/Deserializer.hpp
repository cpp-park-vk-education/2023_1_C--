#pragma once
#include "IDeserializer.hpp"

class Deserializer: public IDeserializer {
public:
    UserData DeserializeUserData(const std::vector<char>& byteArray) override;
    UserInfo DeserializeUserInfo(const std::vector<char>& byteArray)  override;
    RoomInfo DeserializeCreateRoomResponse(const std::vector<char>& byteArray) override;
    Message DeserializeMessage(const std::vector<char>& byteArray) override;
    virtual std::vector<Message> DeserializeRoomMessages(const std::vector<char>& byteArray);
};
