#pragma once
#include <vector>
#include <memory>
#include "AccountData.hpp"
#include "RoomData.hpp"

class ISerializer {
public:
    virtual ~ISerializer() {}
    virtual std::vector<char> SerializeLoginData(const LoginData& data) = 0;
    virtual std::vector<char> SerializeSignupData(const SignupData& data) = 0;
    virtual std::vector<char> SerializeID(const int id) = 0;
    virtual std::vector<char> SerializeMessage(const Message& data) = 0;
    virtual std::vector<char> SerializeRoomInfo(const RoomInfo& data) = 0;
};

using ISerializerSPtr = std::shared_ptr<ISerializer>;
