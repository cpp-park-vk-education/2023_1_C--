#include "RoomSwitcher.hpp"

void RoomSwitcher::ShowMainPage(std::vector<IRoomUPtr> rooms, const UserInfo& userInfo) {
    widgetConroller_->ShowMainPage();
    mainPageUi_->ShowMainPage(std::move(rooms));
    userInfoUi_->ShowUserInfo(userInfo);
}

void RoomSwitcher::ShowRoom(IRoomUPtr room) {
    widgetConroller_->ShowRoomPage();
    roomPageUi_->ShowLastMessages(room->GetLastMessages());
    auto roomInfo = room->GetRoomInfo();
    roomPageUi_->ShowRoomName(roomInfo.name);
}

void RoomSwitcher::ShowRoomInfo(const RoomInfo& roomInfo) {
    widgetConroller_->ShowRoomInfo();
    roomPageUi_->ShowRoomInfo(roomInfo);
}

void RoomSwitcher::ShowLastMessages(const std::vector<Message>& messages) {
    roomPageUi_->ShowLastMessages(messages);
}
