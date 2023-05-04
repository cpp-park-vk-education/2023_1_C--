#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HttpRequestMock.hpp"
#include "HttpResponseMock.hpp"
#include "HttpRequestHandlerMock.hpp"
#include "RoomDbManagerMock.hpp"
#include "HttpRequestMapper.hpp"
#include "CreateRoomService.hpp"
#include "DeleteRoomService.hpp"
#include "GetNewMessageService.hpp"
#include "JoinRoomService.hpp"
#include "LoginService.hpp"
#include "SendMessageService.hpp"
#include "IRoomDBManager.hpp"
#include "IClientDBManager.hpp"
#include "ClientDbManagerMock.hpp"

class HttpRequestMapperTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        auto LoginController = std::make_unique<HttpRequestHandlerMock>(); // Остальные контроллеры не вижу смысла тестить

        LoginControllerAddr = LoginController.get();

        controllers.insert(
            std::make_pair("/login", std::move(LoginController))
        );

        mapper = std::make_unique<HttpRequestMapper>(std::move(controllers));
    }

    void TearDown() override{}

    HttpRequestHandlerMock* LoginControllerAddr;
    std::unique_ptr<HttpRequestMapper> mapper;
    std::map<std::string, std::unique_ptr<IHttpRequestHandler>> controllers;
};


TEST_F(HttpRequestMapperTest, LogginCall)
{
    testing::InSequence s;
    HttpRequestMock request;
    HttpResponseMock response;
    EXPECT_CALL(request, getPath()).Times(1).WillOnce(testing::Return("/login"));
    EXPECT_CALL(*LoginControllerAddr, service(::testing::_, ::testing::_));
    mapper->service(&request, &response);
}

TEST_F(HttpRequestMapperTest, BadControllerCall)
{
    testing::InSequence s;
    HttpRequestMock request;
    EXPECT_CALL(request, getPath()).Times(1).WillOnce(testing::Return("/notexist"));
    EXPECT_CALL(*LoginControllerAddr, service(::testing::_, ::testing::_));

    HttpResponseMock response;

    EXPECT_THROW(mapper->service(&request, &response), std::runtime_error);
}

class CreateRoomServiceTest : public ::testing::Test
{
protected:
    std::shared_ptr<RoomDbManagerMock> manager;
    std::unique_ptr<CreateRoomService> service;
    void SetUp() override
    {
        manager = std::make_shared<RoomDbManagerMock>();

        service = std::make_unique<CreateRoomService>(manager);
    }
};

TEST_F(CreateRoomServiceTest, CreateRoomManagerCall)
{
    EXPECT_CALL(*manager, insertRoom("best_room"));

    service->CreateRoom("best_room");
}

TEST_F(CreateRoomServiceTest, RoomExistYet)
{
    EXPECT_CALL(*manager, insertRoom("existname"));

    EXPECT_THROW(service->CreateRoom("best_room"), std::runtime_error);
}

class DeleteRoomServiceTest : public ::testing::Test
{
protected:
    std::shared_ptr<RoomDbManagerMock> manager;
    std::unique_ptr<DeleteRoomService> service;
    void SetUp() override
    {
        manager = std::make_shared<RoomDbManagerMock>();

        service = std::make_unique<DeleteRoomService>(manager);
    }
};

TEST_F(DeleteRoomServiceTest, DeleteExistRoom)
{
    EXPECT_CALL(*manager, deleteRoom(1));

    service->deleteRoom(1);
}

TEST_F(DeleteRoomServiceTest, BadRoomId)
{
    EXPECT_CALL(*manager, deleteRoom(1337));

    EXPECT_THROW(service->deleteRoom(1);, std::runtime_error);
}

class GetNewMessageServiceTest : public ::testing::Test
{
protected:
    std::shared_ptr<RoomDbManagerMock> manager;
    std::unique_ptr<GetNewMessageService> service;
    void SetUp() override
    {
        manager = std::make_shared<RoomDbManagerMock>();

        service = std::make_unique<GetNewMessageService>(manager);
    }
};

TEST_F(GetNewMessageServiceTest, GetNewMessageCall)
{
    EXPECT_CALL(*manager, getNewMessage(1));

    service->getNewMessage(1);
}

class JoinRoomServiceTest : public ::testing::Test
{
protected:
    std::shared_ptr<RoomDbManagerMock> manager;
    std::unique_ptr<JoinRoomService> service;
    void SetUp() override
    {
        manager = std::make_shared<RoomDbManagerMock>();

        service = std::make_unique<JoinRoomService>(manager);
    }
};

TEST_F(JoinRoomServiceTest, JoinRoomCall)
{
    EXPECT_CALL(*manager, getRoom(1));

    service->GetRoom(1);
}

TEST_F(JoinRoomServiceTest, BadRoomId)
{
    EXPECT_CALL(*manager, getRoom(1));

    EXPECT_THROW(service->GetRoom(1), std::runtime_error);
}

class LoginServiceTest : public ::testing::Test
{
protected:
    std::shared_ptr<MockClientDBManager> manager;
    std::unique_ptr<LoginService> service;
    void SetUp() override
    {
        manager = std::make_shared<MockClientDBManager>();

        service = std::make_unique<LoginService>(manager);
    }
};

TEST_F(LoginServiceTest, LoginManagerCall)
{
    EXPECT_CALL(*manager, getClient("WindowsKonon1337"));

    service->getClient("WindowsKonon1337");
}

TEST_F(LoginServiceTest, BadLogin)
{
    EXPECT_CALL(*manager, getClient("i am not exist"));

    EXPECT_THROW(service->getClient("i am not exist");, std::runtime_error);
}

class SendMessageServiceTest : public ::testing::Test
{
protected:
    std::shared_ptr<RoomDbManagerMock> manager;
    std::unique_ptr<SendMessageService> service;
    void SetUp() override
    {
        manager = std::make_shared<RoomDbManagerMock>();

        service = std::make_unique<SendMessageService>(manager);
    }
};

TEST_F(SendMessageServiceTest, SendMessageCall)
{
    EXPECT_CALL(*manager, insertNewMessage(1, "Hello, world!"));

    service->SendMessage(1, "Hello, world!");
}

TEST_F(SendMessageServiceTest, BadSendMessage)
{
    EXPECT_CALL(*manager, insertNewMessage(1488, "Hello, world!"));

    EXPECT_THROW(service->SendMessage(1488, "Hello, world!"), std::runtime_error);

    EXPECT_CALL(*manager, insertNewMessage(1, ""));

    EXPECT_THROW(service->SendMessage(1488, ""), std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}