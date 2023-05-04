#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AccountNetwork.hpp"
#include "MockReplyHandler.hpp"
#include "MockNetworkManager.hpp"
#include "MockSerializer.hpp"

class AccountNetworkSendTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto networkManagerMock = std::make_unique<MockNetworkManager>();
        auto serializerMock = std::make_unique<MockRequestSerializer>();
        networkManagerMockAddr = networkManagerMock.get();
        serializerMockAddr = serializerMock.get();
        network.SetNetworkManager(std::move(networkManagerMock));
        network.SetRequestSerializer(std::move(serializerMock));
    }

    void TearDown() override {}

protected:
    AccountNetwork network;
    MockNetworkManager* networkManagerMockAddr;
    MockRequestSerializer* serializerMockAddr;
};

TEST_F(AccountNetworkSendTest, CallLogin) {
    testing::InSequence s;
    EXPECT_CALL(*serializerMockAddr, SerializeLoginData(::testing::_));
    EXPECT_CALL(*networkManagerMockAddr, Post(::testing::_, ::testing::_));
    network.Login(LoginData{});
}

TEST_F(AccountNetworkSendTest, CallSignup) {    
    testing::InSequence s;
    EXPECT_CALL(*serializerMockAddr, SerializeSignupData(::testing::_));
    EXPECT_CALL(*networkManagerMockAddr, Post(::testing::_, ::testing::_));    
    network.Signup(SignupData{});
}

TEST_F(AccountNetworkSendTest, CallUserSetting) {    
    testing::InSequence s;
    EXPECT_CALL(*serializerMockAddr, SerializeUserSettingData(::testing::_));
    EXPECT_CALL(*networkManagerMockAddr, Post(::testing::_, ::testing::_));    
    network.UserSetting(UserSettingData{});
}

TEST_F(AccountNetworkSendTest, CallLogout) {    
    EXPECT_CALL(*networkManagerMockAddr, Post(::testing::_, ::testing::_));    
    network.Logout(LogoutData{});
}

class StubSuccesiveResponse : public IResponse {
public:
    unsigned GetStatus(const std::string& url) { return 200; }
    std::vector<char> GetBody() override { return std::vector<char>{}; }
};

class StubUnsuccessfullResponse : public IResponse {
public:
    unsigned int GetStatus(const std::string& url) { return 404; }
    std::vector<char> GetBody() override { return std::vector<char>{}; }
};

class AccountNetworkRecieveTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto replyHanlderMock = std::make_unique<MockAccountReplyHandler>();
        replyHanlderMockAddr = replyHanlderMock.get();
        network.SetReplyHandler(std::move(replyHanlderMock));
        network.SetResponseSerializer(std::make_unique<MockResponseSerializer>());
    }

    void TearDown() override {}

    AccountNetwork network;
    MockAccountReplyHandler* replyHanlderMockAddr;
};

TEST_F(AccountNetworkRecieveTest, CallOnLoginResponse200) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnLoginResponse(200, ::testing::_));
    network.OnLoginResponse(std::make_unique<StubSuccesiveResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnSignupResponse200) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnSignupResponse(200, ::testing::_));
    network.OnSignupResponse(std::make_unique<StubSuccesiveResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnUserSettingResponse200) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnUserSettingResponse(200, ::testing::_));
    network.OnUserSettingResponse(std::make_unique<StubSuccesiveResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnLogoutResponse200) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnLogoutResponse(200));
    network.OnLogoutResponse(std::make_unique<StubSuccesiveResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnLoginResponseWith404) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnLoginResponse(404, ::testing::_));
    network.OnLoginResponse(std::make_unique<StubUnsuccessfullResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnSignupResponseWith404) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnSignupResponse(404, ::testing::_));
    network.OnSignupResponse(std::make_unique<StubUnsuccessfullResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnUserSettingResponseWith404) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnUserSettingResponse(404, ::testing::_));
    network.OnUserSettingResponse(std::make_unique<StubUnsuccessfullResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnLogoutResponseWith404) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnLogoutResponse(404));
    network.OnLogoutResponse(std::make_unique<StubUnsuccessfullResponse>());
}

