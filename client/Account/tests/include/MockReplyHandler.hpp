#pragma once
#include <gmock/gmock.h>
#include "IAccountReplyHandler.hpp"

struct MockAccountReplyHandler : public IAccountReplyHandler {
    MOCK_METHOD(void, OnLoginResponse, (unsigned int, IUserDataUPtr), (override));
    MOCK_METHOD(void, OnSignupResponse, (unsigned int, IUserDataUPtr), (override));
    MOCK_METHOD(void, OnUserSettingResponse, (unsigned int, IUserDataUPtr), (override));
    MOCK_METHOD(void, OnLogoutResponse, (unsigned int), (override));
};
