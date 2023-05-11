#pragma once
#include <gmock/gmock.h>
#include "INetworkManager.hpp"

struct MockNetworkManager : public INetworkManager {
    MOCK_METHOD(void, Post, (IRequestUPtr, Callback), (override));
    MOCK_METHOD(void, Get, (IRequestUPtr, Callback), (override));
};
