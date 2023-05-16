#pragma once
#include <memory>
#include <vector>
#include "RoomData.hpp"

class IRoomReplyHandler {
public:
    virtual ~IRoomReplyHandler() {}
    virtual void OnSendMessageResponse(int statusCode) = 0;
    virtual void OnGetNewMessageResponse(int statusCode, const Message& message) = 0;
    virtual void OnGetRoomMessagesResponse(int statusCode, const std::vector<Message>) = 0;
    virtual void OnCreateRoomResponse(int statusCode, const RoomData& roomData) = 0;
};

using IRoomReplyHandlerSPtr = std::shared_ptr<IRoomReplyHandler>;
