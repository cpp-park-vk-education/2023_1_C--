#pragma once
#include <gmock/gmock.h>
#include "IClientSerializer.hpp"

class MockRequestSerializer : public IAccountRequestSerializer {
public:
    MOCK_METHOD(std::vector<char>, SerializeLoginData, (const LoginData&), (override));
    MOCK_METHOD(std::vector<char>, SerializeSignupData, (const SignupData&), (override));
    MOCK_METHOD(std::vector<char>, SerializeUserSettingData, (const UserSettingData&), (override));
    MOCK_METHOD(std::vector<char>, SerializeLogoutData, (const LogoutData&), (override));
};

class MockResponseSerializer : public IAccountResponseDeserializer {
public:
    MOCK_METHOD(IUserDataUPtr, DeserializeResponse, (const std::vector<char>&), (override));
};
