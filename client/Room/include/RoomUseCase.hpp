#pragma once
#include "IRoomUseCase.hpp"
#include "IRoomReplyHandler.hpp"
#include "IRoomPageUi.hpp"
#include "IMainPageUi.hpp"
#include "IRoomNetwork.hpp"

class RoomUseCase : public IRoomUseCase,
                    public IRoomReplyHandler {
public:
    void CreateRoom(const RoomInfo& roomInfo) override;
    void SendMessage(const Message& message) override;
    void GetNewMessage(const int roomID) override;
    void GetRoomMessage(const int roomID) override;
    void OnSendMessageResponse(int statusCode) override;
    void OnGetNewMessageResponse(int statusCode, const Message& message) override;
    void OnGetRoomMessagesResponse(int statusCode, const std::vector<Message>) override;
    void OnCreateRoomResponse(int statusCode, const RoomData& roomData) override;

    void SetRoomNetwork(IRoomNetworkSPtr roomNetwork) {
        roomNetwork_ = roomNetwork;
    }

    void SetMainPageUi(IMainPageUi* mainPageUi) {
        mainPageUi_ = mainPageUi;
    }

    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

    void SetRoomPageUi(IRoomPageUi* roomUi) {
        roomUi_ = roomUi;
    }

private:
    IRoomNetworkSPtr roomNetwork_;
    IRoomPageUi* roomUi_;
    IRoomSwitcherSPtr roomSwitcher_;
    IMainPageUi* mainPageUi_;
};

