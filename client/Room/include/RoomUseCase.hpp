#pragma once
#include "IRoomUseCase.hpp"
#include "IRoomPageUi.hpp"
#include "IMainPageUi.hpp"
#include "IRoomNetwork.hpp"

class RoomUseCase : public IRoomUseCase {
public:
    void AddUser(const std::string& login) override;
    void SendMessage(const Message& message) override;
    void CreateRoom(const RoomInfo& roomInfo) override;
    void GetMessages(const size_t messageId) override;

    void SetRoomNetwork(IRoomNetworkSPtr roomNetwork) {
        roomNetwork_ = roomNetwork;
    }

    void SetRoomPageUi(IRoomPageUiSPtr roomPageUi) {
        roomPageUi_ = std::move(roomPageUi);
    }

    void SetMainPageUi(IMainPageUiSPtr mainPageUi) {
        mainPageUi_ = std::move(mainPageUi);
    }

private:
    IRoomNetworkSPtr roomNetwork_;
    IRoomPageUiSPtr roomPageUi_;
    IMainPageUiSPtr mainPageUi_;

};

