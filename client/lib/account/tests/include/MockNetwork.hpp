#pragma once
#include <gmock/gmock.h>
#include "IAccountNetwork.hpp"

struct MockAccountNetwork : public IAccountNetwork {
    MOCK_METHOD(void, Login, (const LoginData&), (override));
    MOCK_METHOD(void, Signup, (const SignupData&), (override));
    MOCK_METHOD(void, UserSetting, (const UserSettingData&), (override));
    MOCK_METHOD(void, Logout, (const LogoutData&), (override));
};
