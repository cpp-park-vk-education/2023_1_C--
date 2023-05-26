#pragma once
#include <memory>
#include <vector>
#include "RoomData.hpp"
#include "AccountData.hpp"

class IRoomReplyHandler {
public:
    virtual ~IRoomReplyHandler() {}
    virtual void OnSendMessageResponse() = 0;
    virtual void OnGetNewMessageResponse(Message&& message) = 0;
    virtual void OnCreateRoomResponse(RoomInfo&& roomInfo) = 0;
    virtual void OnGetRoomMessagesResponse(std::vector<Message>&& roomMessages) = 0;
    virtual void OnAddUserResponse(UserInfo&& userInfo) = 0;
    virtual void OnRefreshMainPage(UserData&& data) = 0;
    virtual void ShowMainPageError(std::string&& error) = 0;
    virtual void ShowRoomPageError(std::string&& error) = 0;
    virtual void ShowRoomCreationPageError(std::string&& error) = 0;
};

using IRoomReplyHandlerSPtr = std::shared_ptr<IRoomReplyHandler>;
