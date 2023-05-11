#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "IRoomDBManager.hpp"

class RoomDbManagerMock: public IRoomDBManager {
public:
    MOCK_METHOD(Room, getRoom, (const int), (override));

    MOCK_METHOD(int, insertRoom, (const std::string&), (override));

    MOCK_METHOD(int, insertNewMessage, (const int, const std::string&), (override));

    MOCK_METHOD(Message, getNewMessage, (const int), (override));

    MOCK_METHOD(int, deleteRoom, (const int), (override));

    MOCK_METHOD(int, renameRoom, (const int, const std::string&), (override));

    MOCK_METHOD(int, addClientToRoom, (const int, const std::string&), (override));

    MOCK_METHOD(int, deleteClientFromRoom, (const int, const std::string&), (override));

    MOCK_METHOD(int, changeMessageContext, (const int, const int, const std::string&), (override));
};