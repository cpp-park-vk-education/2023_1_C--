#include <gtest/gtest.h>
#include "AccountUseCase.hpp"
#include "MockNetwork.hpp"
#include "MockAccountUi.hpp"
#include "Errors.hpp"

struct StubCorrectLoginForm : public ILoginForm {
    void validate() const override {}
    LoginData getLoginData() const override { return LoginData{}; }
};

struct StubCorrectSignupForm : public ISignupForm {
    void validate() const override {}
    SignupData getSignupData() const override { return SignupData{}; }
};

struct StubCorrectUserSettingForm : public IUserSettingForm {
    void validate() const override {}
    UserSettingData getUserSettingData() const override { return UserSettingData{}; }
};

struct StubIncorrectLoginForm : public ILoginForm {
    void validate() const override {}
    LoginData getLoginData() const override { throw FormError{"Error"}; }
};

struct StubIncorrectSignupForm : public ISignupForm {
    void validate() const override {}
    SignupData getSignupData() const override { throw FormError{"Error"}; }
};

struct StubIncorrectUserSettingForm : public IUserSettingForm {
    void validate() const override {}
    UserSettingData getUserSettingData() const override { throw FormError{"Error"}; }
};

class AccountUseCaseTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto networkMock = std::make_unique<MockAccountNetwork>();
        networkMockAddr = networkMock.get();
        useCase.SetNetwork(std::move(networkMock));
        
        auto uiMock = std::make_unique<MockAccountUi>();
        uiMockAddr = uiMock.get();
        useCase.SetAccountUi(std::move(uiMock));
    }
    
    void TearDown() override {}

    AccountUseCase useCase;
    MockAccountNetwork* networkMockAddr;
    MockAccountUi* uiMockAddr;  
};

TEST_F(AccountUseCaseTest, CallLoginForCorrectForm) {
    EXPECT_CALL(*networkMockAddr, Login(::testing::_));
    useCase.Login(std::make_unique<StubCorrectLoginForm>());
}

TEST_F(AccountUseCaseTest, CallLoginForIncorrectForm) {
    EXPECT_CALL(*uiMockAddr, ShowError(::testing::_));
    useCase.Login(std::make_unique<StubIncorrectLoginForm>());
}

TEST_F(AccountUseCaseTest, CallSignupForCorrectForm) {
    EXPECT_CALL(*networkMockAddr, Signup(::testing::_));
    useCase.Signup(std::make_unique<StubCorrectSignupForm>());
}

TEST_F(AccountUseCaseTest, CallSignupForIncorrectForm) {
    EXPECT_CALL(*uiMockAddr, ShowError(::testing::_));
    useCase.Signup(std::make_unique<StubIncorrectSignupForm>());
}

TEST_F(AccountUseCaseTest, CallUserSettingForCorrectForm) {
    EXPECT_CALL(*networkMockAddr, UserSetting(::testing::_));
    useCase.UserSetting(std::make_unique<StubCorrectUserSettingForm>());
}

TEST_F(AccountUseCaseTest, CallUserSettingForIncorrectForm) {
    EXPECT_CALL(*uiMockAddr, ShowError(::testing::_));
    useCase.UserSetting(std::make_unique<StubIncorrectUserSettingForm>());
}

TEST_F(AccountUseCaseTest, CallLogout) {
    EXPECT_CALL(*networkMockAddr, Logout(::testing::_));
    useCase.Logout(std::string{});
}
