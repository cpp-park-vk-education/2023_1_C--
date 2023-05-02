#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AccountUseCase.hpp"
#include "Errors.hpp"

struct StubCorrectForm : public IForm {
    void validate() const override {}
    TextData getTextData() const override { return TextData{}; }
};

struct StubIncorrectForm : public IForm {
    void validate() const override { throw FormError{"Error message"}; }
    TextData getTextData() const override { return TextData{}; }
};

struct MockAccountUi : public IAccountUi {
    MOCK_METHOD(void, ShowError, (const std::string& error_message), (override));
};

struct MockAccountNetwork : public IAccountNetwork {
    MOCK_METHOD(void, Login, (const TextData& textData), (override));
    MOCK_METHOD(void, Signup, (const TextData& textData), (override));
    MOCK_METHOD(void, UserSetting, (const TextData& textData), (override));
    MOCK_METHOD(void, Logout, (), (override));
};

class AccountUseCaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        correctForm = std::make_unique<StubCorrectForm>();
        incorrectForm = std::make_unique<StubIncorrectForm>();

        auto networkMock = std::make_unique<MockAccountNetwork>();
        networkMockAddr = networkMock.get();
        useCase.SetNetwork(std::move(networkMock));

        auto uiMock = std::make_unique<MockAccountUi>();
        uiMockAddr = uiMock.get();
        useCase.SetAccountUi(std::move(uiMock));
    }
    
    void TearDown() override {}

protected:
    std::unique_ptr<StubCorrectForm> correctForm;
    std::unique_ptr<StubIncorrectForm> incorrectForm;
    AccountUseCase useCase;
    MockAccountNetwork* networkMockAddr;
    MockAccountUi* uiMockAddr;  
};

TEST_F(AccountUseCaseTest, CallLogiLnForCorrectForm) {
    EXPECT_CALL(*networkMockAddr, Login(::testing::_));
    useCase.Login(std::move(correctForm));
}

TEST_F(AccountUseCaseTest, CallLoginForIncorrectForm) {
    EXPECT_CALL(*uiMockAddr, ShowError(::testing::_));
    useCase.Login(std::move(incorrectForm));
}

TEST_F(AccountUseCaseTest, CallSignupForCorrectForm) {
    EXPECT_CALL(*networkMockAddr, Signup(::testing::_));
    useCase.Signup(std::move(correctForm));
}

TEST_F(AccountUseCaseTest, CallSignupForIncorrectForm) {
    EXPECT_CALL(*uiMockAddr, ShowError(::testing::_));
    useCase.Signup(std::move(incorrectForm));
}

TEST_F(AccountUseCaseTest, CallUserSettingForCorrectForm) {
    EXPECT_CALL(*networkMockAddr, UserSetting(::testing::_));
    useCase.UserSetting(std::move(correctForm));
}

TEST_F(AccountUseCaseTest, CallUserSettingForIncorrectForm) {
    EXPECT_CALL(*uiMockAddr, ShowError(::testing::_));
    useCase.UserSetting(std::move(incorrectForm));
}

TEST_F(AccountUseCaseTest, CallLogout) {
    EXPECT_CALL(*networkMockAddr, Logout());
    useCase.Logout();
}
