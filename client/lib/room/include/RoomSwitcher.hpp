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

    void SetWidgetController(IWidgetControllerUPtr widgetConroller) {
        widgetConroller_ = std::move(widgetConroller);
    }

    void SetRoomPageUi(IRoomPageUiUPtr roomPageUi) {
        roomPageUi_ = std::move(roomPageUi);
    }

    void SetMainPageUi(IMainPageUiUPtr mainPageUi) {
        mainPageUi_ = std::move(mainPageUi);
    }

    void SetUserInfoUi(IUserInfoUiUPtr userInfoUi) {
        userInfoUi_ = std::move(userInfoUi);
    }


private:
    IWidgetControllerUPtr widgetConroller_;
    IRoomPageUiUPtr roomPageUi_;
    IMainPageUiUPtr mainPageUi_;
    IUserInfoUiUPtr userInfoUi_;
};
