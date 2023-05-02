#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AccountReplyHandler.hpp"

struct MockAccountUi : public IAccountUi {
    MOCK_METHOD(void, ShowError, (const std::string& error_message), (override));
};

struct MockWidgetController : public IWidgetController {
    MOCK_METHOD(void, ShowLoginPage, (), (override));
    MOCK_METHOD(void, ShowSignupPage, (), (override));
    MOCK_METHOD(void, ShowUserSettingPage, (), (override));
    MOCK_METHOD(void, ShowRoomPage, (), (override));
    MOCK_METHOD(void, ShowAllRoomsPage, (), (override));
};

struct MockRoomUi : public IRoomUi {
    MOCK_METHOD(void, ShowUserInfo, (UserInfo), (override));
};

class StubUserData : public IUserData {
    std::string GetToken() override {
        return std::string{};
    } 
    UserInfo GetUserInfo() override {
        return UserInfo{};
    }
    std::vector<IRoomUiUPtr> GetUserRooms() override {
        return std::vector<IRoomUiUPtr>{};
    }
};

class AccountReplyHanlderTest : public ::testing::Test {
protected:
    void SetUp() override {
        stubUserData = std::make_unique<StubUserData>();
    }
    void TearDown() override {}

    AccountReplyHandler replyHandler;
    std::unique_ptr<StubUserData>stubUserData;
};

TEST_F(AccountReplyHanlderTest, CallOnLoginResponse200) {
    auto widgetControllerMock = std::make_unique<MockWidgetController>();
    auto roomUiMock = std::make_unique<MockRoomUi>();
    MockWidgetController* widgetControllerMockAddr = widgetControllerMock.get();
    MockRoomUi* roomUiMockAddr = roomUiMock.get();
    replyHandler.SetWidgetController(std::move(widgetControllerMock));
    replyHandler.SetRoomUi(std::move(roomUiMock));
    
    testing::InSequence s;
    EXPECT_CALL(*widgetControllerMockAddr, ShowAllRoomsPage());
    EXPECT_CALL(*roomUiMockAddr, ShowUserInfo(::testing::_));
    replyHandler.OnLoginResponse(200, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnLoginResponse404) {
    auto accountUiMock = std::make_unique<MockAccountUi>();
    MockAccountUi* accountUiMockAddr = accountUiMock.get();
    replyHandler.SetAccountUi(std::move(accountUiMock));
    
    EXPECT_CALL(*accountUiMockAddr, ShowError(::testing::_));
    replyHandler.OnLoginResponse(404, std::move(stubUserData));
}
