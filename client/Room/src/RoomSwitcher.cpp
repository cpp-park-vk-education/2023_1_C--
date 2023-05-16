#include "RoomSwitcher.hpp"

void RoomSwitcher::ShowMainPage(std::vector<RoomData> rooms, const UserInfo& userInfo) {
    widgetConroller_->ShowMainPage();
    mainPageUi_->ShowMainPage(std::move(rooms));
    mainPageUi_->SetUserInfo(userInfo);
}

void RoomSwitcher::BackOnMainPage() {
    widgetConroller_->ShowMainPage();
}

void RoomSwitcher::ShowRoom(const RoomData& roomData, const UserInfo userInfo) {
    widgetConroller_->ShowRoomPage();
    roomPageUi_->SetRoomData(roomData);
    roomPageUi_->SetUserInfo(userInfo);
}

void RoomSwitcher::ShowLastMessages(const std::vector<Message>& messages) {}
void RoomSwitcher::ShowOldMessages(const std::vector<Message>& messages) {}

void RoomSwitcher::ShowRoomSearchPage() {
    widgetConroller_->ShowRoomSearchPage();
}

void RoomSwitcher::ShowRoomCreationPage() {
    widgetConroller_->ShowRoomCreationPage();
}
