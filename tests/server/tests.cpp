#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "HttpRequestMock.hpp"
#include "HttpResponseMock.hpp"
#include "HttpRequestHandlerMock.hpp"

TEST(HttpRequestHandlerTest, LoginControllerSimulation)
{
    HttpRequestHandlerMock requestMapper;

    HttpRequestMock httpRequest;

    EXPECT_CALL(httpRequest, getPath()).Times(1).WillOnce(testing::Return("/login"));

    HttpResponseMock httpResponse;

    EXPECT_CALL(httpResponse, setBody("user")).Times(1);

    EXPECT_CALL(requestMapper, service(&httpRequest, &httpResponse)).Times(1);

    requestMapper.service(&httpRequest, &httpResponse);

    // типо внутри функции, хз как такое тестить правильно

    if (httpRequest.getPath() == "/login")
        httpResponse.setBody("user");
}

TEST(HttpRequestHandlerTest, BadControllerSimulation)
{
    HttpRequestHandlerMock requestMapper;

    HttpRequestMock httpRequest;

    HttpResponseMock httpResponse;

    EXPECT_CALL(requestMapper, service(&httpRequest, &httpResponse)).Times(1).WillOnce(testing::Throw(std::runtime_error("")));

    EXPECT_THROW(requestMapper.service(&httpRequest, &httpResponse), std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}