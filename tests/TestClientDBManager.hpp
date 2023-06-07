#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ClientDBManager.hpp"

class MockClientDBManager: public IClientDBManager {
public:
    MOCK_METHOD(Client, getClient, (const std::string&), (override));

    MOCK_METHOD(int, changeLogin, (const std::string&, const std::string&), (override));

    MOCK_METHOD(int, changePassword, (const std::string&, const std::string&), (override));

    MOCK_METHOD(int, setFirstname, (const std::string&, const std::string&), (override));

    MOCK_METHOD(int, setLastname, (const std::string&, const std::string&), (override));
};