#include <gtest/gtest.h>
#include "AccountReplyHandler.hpp"
#include "MockWidgetController.hpp"
#include "MockAccountUi.hpp"
#include "MockRoomSwithcer.hpp"

class StubUserData : public IUserData {
public:
    std::string GetToken() override { return std::string{}; } 

    UserInfo GetUserInfo() override { return UserInfo{}; }

    std::vector<IRoomUPtr> GetUserRooms() override {
        return std::vector<IRoomUPtr>{};
    }
};

class AccountReplyHanlderTest : public ::testing::Test {
protected:
    void SetUp() override {
        stubUserData = std::make_unique<StubUserData>();
        auto accountUiMock = std::make_unique<MockAccountUi>();
        auto widgetControllerMock = std::make_unique<MockWidgetController>();
        auto roomSwitcherMock = std::make_unique<MockRoomSwitcher>();
        widgetControllerMockAddr = widgetControllerMock.get();
        roomSwitcherMockAddr = roomSwitcherMock.get();
        accountUiMockAddr = accountUiMock.get();
        replyHandler.SetWidgetController(std::move(widgetControllerMock));
        replyHandler.SetRoomSwitcher(std::move(roomSwitcherMock));
        replyHandler.SetAccountUi(std::move(accountUiMock));
    }   
    void TearDown() override {}

    AccountReplyHandler replyHandler;
    std::unique_ptr<StubUserData>stubUserData;
    MockWidgetController* widgetControllerMockAddr;
    MockRoomSwitcher* roomSwitcherMockAddr;
    MockAccountUi* accountUiMockAddr;
};

TEST_F(AccountReplyHanlderTest, CallOnLoginResponse200) {
    testing::InSequence s;
    EXPECT_CALL(*widgetControllerMockAddr, ShowAllRoomsPage());
    EXPECT_CALL(*roomSwitcherMockAddr, ShowMainPage(::testing::_));
    replyHandler.OnLoginResponse(200, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnLoginResponse404) {   
    EXPECT_CALL(*accountUiMockAddr, ShowError(::testing::_));
    replyHandler.OnLoginResponse(404, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnSignupResponse200) {
    testing::InSequence s;
    EXPECT_CALL(*widgetControllerMockAddr, ShowAllRoomsPage());
    EXPECT_CALL(*roomSwitcherMockAddr, ShowMainPage(::testing::_));
    replyHandler.OnSignupResponse(200, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnSignupResponse404) {
    EXPECT_CALL(*accountUiMockAddr, ShowError(::testing::_));
    replyHandler.OnSignupResponse(404, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnUserSettingResponse200) {
    EXPECT_CALL(*widgetControllerMockAddr, ShowAllRoomsPage());
    EXPECT_CALL(*roomSwitcherMockAddr, ShowMainPage(::testing::_));
    replyHandler.OnUserSettingResponse(200, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnUserSettingResponse404) {
    EXPECT_CALL(*accountUiMockAddr, ShowError(::testing::_));
    replyHandler.OnUserSettingResponse(404, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnLogoutResponse200) {
    EXPECT_CALL(*widgetControllerMockAddr, ShowLoginPage());
    replyHandler.OnLogoutResponse(200);
}

TEST_F(AccountReplyHanlderTest, CallOnLogoutResponse404) {
    EXPECT_CALL(*accountUiMockAddr, ShowError(::testing::_));
    replyHandler.OnLogoutResponse(404);
}