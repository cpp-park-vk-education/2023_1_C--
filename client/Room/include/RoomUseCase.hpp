#pragma once
#include "IRoomPage.hpp"
#include "IMainPage.hpp"
#include "IRoomUseCase.hpp"
#include "IRoomReplyHandler.hpp"
#include "IAccountUseCase.hpp"
#include "IRoomNetwork.hpp"
#include "IWidgetController.hpp"

class RoomUseCase : public IRoomUseCase,
                    public IRoomReplyHandler {
public:
    void CreateRoom(std::string&& name,
                    std::vector<std::string>&& members) override;
    void SendMessage(Message&& message) override;
    void GetNewMessage(const int roomID) override;
    void GetRoomMessages(const int roomID) override;
    void AddUser(const int roomID, const std::string& login) override;
    void RefreshMainPage() override;
    void ShowMainPage() override;
    void ShowMainPage(UserData&& userData) override;
    void OnSendMessageResponse(const int statusCode) override;
    void OnGetNewMessageResponse(const int statusCode, Message&& message) override;
    void OnGetRoomMessagesResponse(const int statusCode, std::vector<Message>&& messages) override;
    void OnCreateRoomResponse(const int statusCode, RoomInfo&& roomInfo) override;
    void OnAddUserResponse(const int statusCode, UserInfo&& userInfo) override;
    void OnRefreshMainPage(const int statusCode, const UserData& data) override;

    void SetRoomNetwork(IRoomNetworkSPtr roomNetwork) {
        roomNetwork_ = roomNetwork;
    }

    void SetRoomPage(IRoomPage* roomPage) {
        roomPage_ = roomPage;
    }

    void SetMainPage(IMainPage* mainPage) {
        mainPage_ = mainPage;
    }

    void SetAccountUseCase(IAccountUseCaseSPtr accountUseCase) {
        accountUseCase_ = accountUseCase;
    }

    void SetWidgetController(IWidgetController* controller) {
        controller_ = controller;
    }

private:
    RoomInfo room;
    Message tempMessage;
    std::vector<Message> roomMessages;
    UserData userData_;
    IRoomPage* roomPage_;
    IMainPage* mainPage_;
    IAccountUseCaseSPtr accountUseCase_;
    IRoomNetworkSPtr roomNetwork_;
    IWidgetController* controller_;
    RoomInfo FindRoomInfo(const int roomID);
    void AddUserIntoRoom(UserInfo&& userInfo);
};
