#pragma once
#include <memory>
#include <vector>

#include "RoomData.hpp"

class IRoomReplyHandler {
public:
    virtual ~IRoomReplyHandler() {}
    virtual void OnAddUserResponse(unsigned int statusCode, 
                                   const RoomInfo& roomInfo) = 0;
    virtual void OnSendMessageResponse(unsigned int statusCode, 
                                       const std::vector<Message>& newMessage) = 0;
    virtual void OnGetMessagesResponse(unsigned int statusCode,
                                       const std::vector<Message>& messages) = 0;
    virtual void OnCreateRoomResponse(unsigned int statusCode, IRoomUPtr room) = 0;
};

using IRoomReplyHandlerUPtr = std::unique_ptr<IRoomReplyHandler>;
