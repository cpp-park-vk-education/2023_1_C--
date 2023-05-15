#include "RoomSwitcher.hpp"

void RoomSwitcher::ShowMainPage(std::vector<RoomData> rooms, const UserInfo& userInfo) {
    widgetConroller_->ShowMainPage();
    mainPageUi_->ShowMainPage(std::move(rooms));
}

void RoomSwitcher::BackOnMainPage() {
    widgetConroller_->ShowMainPage();
}

void RoomSwitcher::ShowRoom(RoomData room) {
    widgetConroller_->ShowRoomPage();
    // roomPageUi_->ShowLastMessages(room.lastMessages);
    // auto roomInfo = room.info;
    // roomPageUi_->ShowRoomName(roomInfo.name);
}

// void RoomSwitcher::ShowRoomInfo(const RoomInfo& roomInfo) {
//     widgetConroller_->ShowRoomInfo();
//     roomPageUi_->ShowRoomInfo(roomInfo);
// }

void RoomSwitcher::ShowLastMessages(const std::vector<Message>& messages) {}

void RoomSwitcher::ShowOldMessages(const std::vector<Message>& messages) {}

void RoomSwitcher::ShowRoomSearchPage() {
    widgetConroller_->ShowRoomSearchPage();
}

void RoomSwitcher::ShowRoomCreationPage() {
    widgetConroller_->ShowRoomCreationPage();
}
