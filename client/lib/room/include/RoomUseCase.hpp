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

    void SetRoomNetwork(IRoomNetworkUPtr roomNetwork) {
        roomNetwork_ = std::move(roomNetwork);
    }

    void SetRoomPageUi(IRoomPageUiUPtr roomPageUi) {
        roomPageUi_ = std::move(roomPageUi);
    }

    void SetMainPageUi(IMainPageUiUPtr mainPageUi) {
        mainPageUi_ = std::move(mainPageUi);
    }

private:
    IRoomNetworkUPtr roomNetwork_;
    IRoomPageUiUPtr roomPageUi_;
    IMainPageUiUPtr mainPageUi_;

};

