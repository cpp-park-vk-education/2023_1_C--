#pragma once
#include <gmock/gmock.h>
#include "IAccountUi.hpp"

struct MockAccountUi : public IAccountUi {
    MOCK_METHOD(void, ShowError, (const std::string& error_message), (override));
};
