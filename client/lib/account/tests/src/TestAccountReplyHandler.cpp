#include <gtest/gtest.h>
#include "AccountReplyHandler.hpp"
#include "MockWidgetController.hpp"
#include "MockAccountUi.hpp"
#include "MockRoomUi.hpp"

class StubUserData : public IUserData {
public:
    std::string GetToken() override { return std::string{}; } 
    
    UserInfo GetUserInfo() override { return UserInfo{}; }
    
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

TEST_F(AccountReplyHanlderTest, CallOnSignupResponse200) {
    auto widgetControllerMock = std::make_unique<MockWidgetController>();
    auto roomUiMock = std::make_unique<MockRoomUi>();
    MockWidgetController* widgetControllerMockAddr = widgetControllerMock.get();
    MockRoomUi* roomUiMockAddr = roomUiMock.get();
    replyHandler.SetWidgetController(std::move(widgetControllerMock));
    replyHandler.SetRoomUi(std::move(roomUiMock));
    
    testing::InSequence s;
    EXPECT_CALL(*widgetControllerMockAddr, ShowAllRoomsPage());
    EXPECT_CALL(*roomUiMockAddr, ShowUserInfo(::testing::_));
    replyHandler.OnSignupResponse(200, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnSignupResponse404) {
    auto accountUiMock = std::make_unique<MockAccountUi>();
    MockAccountUi* accountUiMockAddr = accountUiMock.get();
    replyHandler.SetAccountUi(std::move(accountUiMock));
    
    EXPECT_CALL(*accountUiMockAddr, ShowError(::testing::_));
    replyHandler.OnSignupResponse(404, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnUserSettingResponse200) {
    auto widgetControllerMock = std::make_unique<MockWidgetController>();
    MockWidgetController* widgetControllerMockAddr = widgetControllerMock.get();
    replyHandler.SetWidgetController(std::move(widgetControllerMock));
    
    EXPECT_CALL(*widgetControllerMockAddr, ShowUserSettingPage());
    replyHandler.OnUserSettingResponse(200, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnUserSettingResponse404) {
    auto accountUiMock = std::make_unique<MockAccountUi>();
    MockAccountUi* accountUiMockAddr = accountUiMock.get();
    replyHandler.SetAccountUi(std::move(accountUiMock));
    
    EXPECT_CALL(*accountUiMockAddr, ShowError(::testing::_));
    replyHandler.OnUserSettingResponse(404, std::move(stubUserData));
}

TEST_F(AccountReplyHanlderTest, CallOnLogoutResponse200) {
    auto widgetControllerMock = std::make_unique<MockWidgetController>();
    MockWidgetController* widgetControllerMockAddr = widgetControllerMock.get();
    replyHandler.SetWidgetController(std::move(widgetControllerMock));
    
    EXPECT_CALL(*widgetControllerMockAddr, ShowLoginPage());
    replyHandler.OnLogoutResponse(200);
}

TEST_F(AccountReplyHanlderTest, CallOnLogoutResponse404) {
    auto accountUiMock = std::make_unique<MockAccountUi>();
    MockAccountUi* accountUiMockAddr = accountUiMock.get();
    replyHandler.SetAccountUi(std::move(accountUiMock));
    
    EXPECT_CALL(*accountUiMockAddr, ShowError(::testing::_));
    replyHandler.OnLogoutResponse(404);
}