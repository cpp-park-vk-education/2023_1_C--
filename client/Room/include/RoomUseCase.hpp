#pragma once
#include "IRoomPage.hpp"
#include "IMainPage.hpp"
#include "IRoomCreationPage.hpp"
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
    void OnSendMessageResponse();
    void OnGetNewMessageResponse(Message&& message) override;
    void OnGetRoomMessagesResponse(std::vector<Message>&& messages) override;
    void OnCreateRoomResponse(RoomInfo&& roomInfo) override;
    void OnAddUserResponse(UserInfo&& userInfo) override;
    void OnRefreshMainPage(UserData&&) override;
    void ShowMainPageError(std::string&& error) override;
    void ShowRoomPageError(std::string&& error) override;
    void ShowRoomCreationPageError(std::string&& error) override;


    void SetRoomNetwork(IRoomNetworkSPtr roomNetwork) {
        roomNetwork_ = roomNetwork;
    }

    void SetRoomPage(IRoomPage* roomPage) {
        roomPage_ = roomPage;
    }

    void SetMainPage(IMainPage* mainPage) {
        mainPage_ = mainPage;
    }

    void SetRoomCreationPage(IRoomCreationPage* roomCreationPage) {
        roomCreationPage_ = roomCreationPage;
    }

    void SetAccountUseCase(IAccountUseCaseSPtr accountUseCase) {
        accountUseCase_ = accountUseCase;
    }

    void SetWidgetController(IWidgetController* controller) {
        controller_ = controller;
    }

private:
    UserData data;
    RoomInfo room;
    Message tempMessage;
    std::vector<Message> roomMessages;
    IRoomPage* roomPage_;
    IMainPage* mainPage_;
    IRoomCreationPage* roomCreationPage_;
    IAccountUseCaseSPtr accountUseCase_;
    IRoomNetworkSPtr roomNetwork_;
    IWidgetController* controller_;
    RoomInfo FindRoomInfo(const int roomID);
    void AddUserIntoRoom(UserInfo&& userInfo);
};
