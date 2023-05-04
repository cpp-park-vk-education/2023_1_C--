#pragma once
#include <gmock/gmock.h>
#include "IRoomUi.hpp"

struct MockRoomUi : public IRoomUi {
    MOCK_METHOD(void, ShowUserInfo, (UserInfo), (override));
};
