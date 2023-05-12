#pragma once
#include <gmock/gmock.h>
#include "IRoomSwitcher.hpp"

    // virtual void ShowMainPage(std::vector<IRoomUPtr> rooms,
    //                           const UserInfo& userInfo) = 0;
    // virtual void ShowRoom(IRoomUPtr room) = 0;
    // virtual void ShowRoomInfo(const RoomInfo& roomInfo) = 0;
    // virtual void ShowLastMessages(const std::vector<Message>& messages) = 0;
    // virtual void ShowOldMessages(const std::vector<Message>& messages) = 0;


struct MockRoomSwitcher : public IRoomSwitcher {
    MOCK_METHOD(void, ShowMainPage, ((std::vector<IRoomUPtr>), (const UserInfo&)), (override));
    MOCK_METHOD(void, ShowRoom, (IRoomUPtr), (override));
    MOCK_METHOD(void, ShowRoomInfo, (const RoomInfo&), (override));
    MOCK_METHOD(void, ShowLastMessages, (const std::vector<Message>&), (override));
    MOCK_METHOD(void, ShowOldMessages, (const std::vector<Message>&), (override));
};
