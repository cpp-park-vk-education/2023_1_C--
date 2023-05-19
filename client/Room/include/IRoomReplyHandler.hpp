#pragma once
#include <memory>
#include <vector>
#include "RoomData.hpp"
#include "AccountData.hpp"

class IRoomReplyHandler {
public:
    virtual ~IRoomReplyHandler() {}
    virtual void OnSendMessageResponse(const int statusCode) = 0;
    virtual void OnGetNewMessageResponse(const int statusCode, Message&& message) = 0;
    virtual void OnCreateRoomResponse(const int statusCode, RoomInfo&& roomInfo) = 0;
    virtual void OnGetRoomMessagesResponse(const int statusCode, std::vector<Message>&& roomMessages) = 0;
    virtual void OnAddUserResponse(const int statusCode, UserInfo&& userInfo) = 0;
};

using IRoomReplyHandlerSPtr = std::shared_ptr<IRoomReplyHandler>;
