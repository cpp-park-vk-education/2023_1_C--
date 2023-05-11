#pragma once
#include <gmock/gmock.h>
#include "IWidgetController.hpp"

struct MockWidgetController : public IWidgetController {
    MOCK_METHOD(void, ShowLoginPage, (), (override));
    MOCK_METHOD(void, ShowSignupPage, (), (override));
    MOCK_METHOD(void, ShowUserSettingPage, (), (override));
    MOCK_METHOD(void, ShowRoomPage, (), (override));
    MOCK_METHOD(void, ShowAllRoomsPage, (), (override));
};
