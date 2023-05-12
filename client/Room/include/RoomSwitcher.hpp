#pragma once
#include "IRoomSwitcher.hpp"
#include "IRoomPageUi.hpp"
#include "IUserInfoUi.hpp"
#include "IMainPageUi.hpp"
#include "IWidgetController.hpp"

class RoomSwitcher : public IRoomSwitcher {
public:
    void ShowMainPage(std::vector<IRoomUPtr> rooms, const UserInfo& userInfo) override;
    void ShowRoom(IRoomUPtr room) override;
    void ShowRoomInfo(const RoomInfo& roomInfo) override;
    void ShowLastMessages(const std::vector<Message>& messages) override;
    void ShowOldMessages(const std::vector<Message>& messages) override;

    void SetWidgetController(IWidgetControllerSPtr widgetConroller) {
        widgetConroller_ = widgetConroller;
    }

    void SetRoomPageUi(IRoomPageUiSPtr roomPageUi) {
        roomPageUi_ = roomPageUi;
    }

    void SetMainPageUi(IMainPageUiSPtr mainPageUi) {
        mainPageUi_ = mainPageUi;
    }

    void SetUserInfoUi(IUserInfoUiSPtr userInfoUi) {
        userInfoUi_ = userInfoUi;
    }


private:
    IWidgetControllerSPtr widgetConroller_;
    IRoomPageUiSPtr roomPageUi_;
    IMainPageUiSPtr mainPageUi_;
    IUserInfoUiSPtr userInfoUi_;
};
