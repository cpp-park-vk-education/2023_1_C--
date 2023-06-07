#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "DBManager.hpp"

class MockDBManager: public IDBManager {
public:
    MOCK_METHOD(int, connect, (const std::string&), (override));

    MOCK_METHOD(std::vector<std::vector<std::string>>, exec, (const std::string&), (override));
};
