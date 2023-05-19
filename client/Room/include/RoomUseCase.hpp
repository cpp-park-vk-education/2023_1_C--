#pragma once
#include "IRoomPage.hpp"
#include "IMainPage.hpp"
#include "IRoomUseCase.hpp"
#include "IRoomReplyHandler.hpp"
#include "IAccountUseCase.hpp"
#include "IRoomNetwork.hpp"

class RoomUseCase : public IRoomUseCase,
                    public IRoomReplyHandler {
public:
    void CreateRoom(RoomInfo&& roomInfo) override;
    void SendMessage(Message&& message) override;
    void GetNewMessage(const int roomID) override;
    void GetRoomMessages(const int roomID) override;
    void ShowMainPage(UserData&& userData) override;
    void OnSendMessageResponse(int statusCode) override;
    void OnGetNewMessageResponse(int statusCode, Message&& message) override;
    void OnGetRoomMessagesResponse(int statusCode, std::vector<Message>&& messages) override;
    void OnCreateRoomResponse(int statusCode, RoomInfo&& roomInfo) override;

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

private:
    RoomInfo currentRoom;
    UserData userData_;
    IRoomPage* roomPage_;
    IMainPage* mainPage_;
    IAccountUseCaseSPtr accountUseCase_;
    IRoomNetworkSPtr roomNetwork_;
    RoomInfo FindRoomInfo(const int roomID);
};
