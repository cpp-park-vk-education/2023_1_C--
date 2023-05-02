#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AccountNetwork.hpp"

struct MockTextSerializer : public ITextSerializer {
    MOCK_METHOD(std::vector<char>, SerializeText, (TextData), (override));
    MOCK_METHOD(IUserDataUPtr, DeserializeText, (std::vector<char>), (override));
};

struct MockNetworkManager : public INetworkManager {
    MOCK_METHOD(void, Post, (IRequestUPtr, Callback), (override));
    MOCK_METHOD(void, Get, (IRequestUPtr, Callback), (override));
};

struct MockAccountReplyHandler : public IAccountReplyHandler {
    MOCK_METHOD(void, OnLoginResponse, (unsigned int, IUserDataUPtr), (override));
    MOCK_METHOD(void, OnSignupResponse, (unsigned int, IUserDataUPtr), (override));
    MOCK_METHOD(void, OnUserSettingResponse, (unsigned int, IUserDataUPtr), (override));
};

class AccountNetworkSendTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto networkManagerMock = std::make_unique<MockNetworkManager>();
        auto serializerMock = std::make_unique<MockTextSerializer>();

        networkManagerMockAddr = networkManagerMock.get();
        serializerMockAddr = serializerMock.get();

        network.SetNetworkManager(std::move(networkManagerMock));
        network.SetSerializer(std::move(serializerMock));
    }

    void TearDown() override {}

protected:
    AccountNetwork network;
    MockNetworkManager* networkManagerMockAddr;
    MockTextSerializer* serializerMockAddr;
};

TEST_F(AccountNetworkSendTest, CallLogin) {    
    testing::InSequence s;
    EXPECT_CALL(*serializerMockAddr, SerializeText(::testing::_));
    EXPECT_CALL(*networkManagerMockAddr, Post(::testing::_, ::testing::_));
    network.Login(TextData{});
}

TEST_F(AccountNetworkSendTest, CallSignup) {    
    testing::InSequence s;
    EXPECT_CALL(*serializerMockAddr, SerializeText(::testing::_));
    EXPECT_CALL(*networkManagerMockAddr, Post(::testing::_, ::testing::_));    
    network.Signup(TextData{});
}

TEST_F(AccountNetworkSendTest, CallUserSetting) {    
    testing::InSequence s;
    EXPECT_CALL(*serializerMockAddr, SerializeText(::testing::_));
    EXPECT_CALL(*networkManagerMockAddr, Post(::testing::_, ::testing::_));    
    network.UserSetting(TextData{});
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
        network.SetSerializer(std::make_unique<MockTextSerializer>());
    }

    void TearDown() override {}

protected:
    AccountNetwork network;
    MockAccountReplyHandler* replyHanlderMockAddr;
};

TEST_F(AccountNetworkRecieveTest, CallOnLoginResponse) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnLoginResponse(200, ::testing::_));
    network.OnLoginResponse(std::make_unique<StubSuccesiveResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnSignupResponse) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnSignupResponse(200, ::testing::_));
    network.OnSignupResponse(std::make_unique<StubSuccesiveResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnUserSettingResponse) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnUserSettingResponse(200, ::testing::_));
    network.OnUserSettingResponse(std::make_unique<StubSuccesiveResponse>());
}

TEST_F(AccountNetworkRecieveTest, CallOnLoginResponseWith404) {    
    EXPECT_CALL(*replyHanlderMockAddr, OnLoginResponse(404, ::testing::_));
    network.OnLoginResponse(std::make_unique<StubUnsuccessfullResponse>());
}
