#pragma once
#include <vector>
#include <memory>
#include "LoginData.hpp"
#include "SignupData.hpp"
#include "Message.hpp"

class ISerializer {
public:
    virtual ~ISerializer() {}
    virtual std::vector<char> SerializeLoginData(const LoginData& data) = 0;
    virtual std::vector<char> SerializeSignupData(const SignupData& data) = 0;
    virtual std::vector<char> SerializeMessage(const Message& data) = 0;
    virtual std::vector<char> SerializeRoomCreation(const std::string& name,
                                                    const std::vector<std::string>& members) = 0;
    virtual std::vector<char> SerializeJoiningUser(const int roomID, const std::string& login) = 0;
};

using ISerializerSPtr = std::shared_ptr<ISerializer>;
