#pragma once
#include <gmock/gmock.h>
#include "IRoomSwitcher.hpp"

struct MockRoomSwitcher : public IRoomSwitcher {
    MOCK_METHOD(void, ShowMainPage, (IUserDataUPtr), (override));
};
