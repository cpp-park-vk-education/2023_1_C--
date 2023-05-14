#pragma once
#include "IRoomSwitcher.hpp"
#include "IRoomPageUi.hpp"
#include "IUserInfoUi.hpp"
#include "IMainPageUi.hpp"
#include "IWidgetController.hpp"

class RoomSwitcher : public IRoomSwitcher {
public:
    void ShowMainPage(std::vector<RoomData> rooms, const UserInfo& userInfo) override;
    void ShowRoom(RoomData room) override;
    void ShowRoomInfo(const RoomInfo& roomInfo) override;
    void ShowLastMessages(const std::vector<Message>& messages) override;
    void ShowOldMessages(const std::vector<Message>& messages) override;

    void SetWidgetController(IWidgetController* widgetConroller) {
        widgetConroller_ = widgetConroller;
    }

    void SetRoomPageUi(IRoomPageUi* roomPageUi) {
        roomPageUi_ = roomPageUi;
    }

    void SetMainPageUi(IMainPageUi* mainPageUi) {
        mainPageUi_ = mainPageUi;
    }

    void SetUserInfoUi(IUserInfoUi* userInfoUi) {
        userInfoUi_ = userInfoUi;
    }


private:
    IWidgetController* widgetConroller_;
    IRoomPageUi* roomPageUi_;
    IMainPageUi* mainPageUi_;
    IUserInfoUi* userInfoUi_;
};
