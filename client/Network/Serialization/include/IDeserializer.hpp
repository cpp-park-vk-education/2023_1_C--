#pragma once
#include <vector>
#include <memory>
#include "UserData.hpp"
#include "Message.hpp"

class IDeserializer {
public:
    virtual ~IDeserializer() {}
    virtual UserInfo DeserializeUserInfo(std::vector<char> byteArray)  = 0;
    virtual UserData DeserializeUserData(std::vector<char> byteArray)  = 0;
    virtual RoomInfo DeserializeCreateRoomResponse(std::vector<char> byteArray) = 0;
    virtual Message DeserializeMessage(std::vector<char> byteArray) = 0;
    virtual std::vector<Message> DeserializeRoomMessages(std::vector<char> byteArray) = 0;
};

using IDeserializerSPtr = std::shared_ptr<IDeserializer>;