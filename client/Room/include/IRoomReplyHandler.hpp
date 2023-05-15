#pragma once
#include <memory>
#include <vector>

#include "RoomData.hpp"

class IRoomReplyHandler {
public:
    virtual ~IRoomReplyHandler() {}
    virtual void OnAddUserResponse(const int statusCode, 
                                   const RoomInfo& roomInfo) = 0;
                                   
    virtual void OnSendMessageResponse(const int statusCode) = 0;

    virtual void OnGetMessagesResponse(const int statusCode,
                                       const std::vector<Message>& messages) = 0;
    virtual void OnCreateRoomResponse(const int statusCode, RoomData room) = 0;
};

using IRoomReplyHandlerSPtr = std::shared_ptr<IRoomReplyHandler>;
