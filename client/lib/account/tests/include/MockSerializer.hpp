#pragma once
#include <gmock/gmock.h>
#include "IAccountSerializer.hpp"

class MockRequestSerializer : public IAccountRequestSerializer {
public:
    MOCK_METHOD(std::vector<char>, SerializeLoginData, (const LoginData&), (override));
    MOCK_METHOD(std::vector<char>, SerializeSignupData, (const SignupData&), (override));
    MOCK_METHOD(std::vector<char>, SerializeUserSettingData, (const UserSettingData&), (override));
    MOCK_METHOD(std::vector<char>, SerializeLogoutData, (const LogoutData&), (override));
    MOCK_METHOD(LoginData, DeserializeLoginData, (const std::vector<char>&), (override));
    MOCK_METHOD(SignupData, DeserializeSignupData, (const std::vector<char>&), (override));
    MOCK_METHOD(UserSettingData, DeserializeUserSettingData, (const std::vector<char>&), (override));
    MOCK_METHOD(LogoutData, DeserializeLogoutData, (const std::vector<char>&), (override));
};

class MockResponseSerializer : public IAccountResponseSerializer {
public:
    MOCK_METHOD(std::vector<char>, SerializeResponse, (IUserDataUPtr), (override));
    MOCK_METHOD(IUserDataUPtr, DeserializeResponse, (const std::vector<char>&), (override));
};
