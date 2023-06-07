#pragma once
#include <vector>
#include <memory>
#include "UserData.hpp"
#include "Message.hpp"

class IDeserializer {
public:
    virtual ~IDeserializer() {}
    virtual UserInfo DeserializeUserInfo(const std::vector<char>& byteArray)  = 0;
    virtual UserData DeserializeUserData(const std::vector<char>& byteArray)  = 0;
    virtual RoomInfo DeserializeCreateRoomResponse(const std::vector<char>& byteArray) = 0;
    virtual Message DeserializeMessage(const std::vector<char>& byteArray) = 0;
    virtual std::vector<Message> DeserializeRoomMessages(const std::vector<char>& byteArray) = 0;
};

using IDeserializerSPtr = std::shared_ptr<IDeserializer>;
