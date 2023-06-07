#include <gtest/gtest.h>
#include "AccountSwitcher.hpp"
#include "MockWidgetController.hpp"

class AccountPagesSwitcherTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto widgetController = std::make_unique<MockWidgetController>();
        mockAddr = widgetController.get();
        pageSwitcher.SetWidgetController(std::move(widgetController));
    }

    void TearDown() override {}

    MockWidgetController* mockAddr;
    AccountSwitcher pageSwitcher;

};

TEST_F(AccountPagesSwitcherTest, CallShowLoginPage) {
    EXPECT_CALL(*mockAddr, ShowLoginPage());
    pageSwitcher.ShowLoginPage();
}

TEST_F(AccountPagesSwitcherTest, CallShowSignupPage) {
    EXPECT_CALL(*mockAddr, ShowSignupPage());
    pageSwitcher.ShowSignupPage();
}

TEST_F(AccountPagesSwitcherTest, CallShowUserSettingPage) {
    EXPECT_CALL(*mockAddr, ShowUserSettingPage());
    pageSwitcher.ShowUserSettingPage();
}
