#include "AppController.hpp"

AppController::AppController() {
    // accountNetwork.SetNetworkManager();
    accountNetwork.SetReplyHandler(std::make_shared<AccountReplyHandler>(accountReplyHandler));
    // accountReplyHandler.SetAccountUi();
    accountReplyHandler.SetRoomSwitcher(std::make_shared<RoomSwitcher>(roomSwitcher));
    // // accountSwitcher.SetWidgetController(std::make_shared<>());
    // // accountUseCase.SetAccountUi();
    accountUseCase.SetNetwork(std::make_shared<AccountNetwork>(accountNetwork));
    // // accountUi.Set();

    // // roomNetwork.SetNetworkManager();
    roomNetwork.SetReplyHandler(std::make_shared<RoomReplyHandler>(roomReplyHandler));
    // // roomReplyHandler.SetAccountUi();
    roomReplyHandler.SetRoomSwitcher(std::make_shared<RoomSwitcher>(roomSwitcher));
    // // roomSwitcher.SetWidgetController(std::make_shared<>());
    // // roomUseCase.SetAccountUi();
    roomUseCase.SetRoomNetwork(std::make_shared<RoomNetwork>(roomNetwork));
    // // roomPageUi.Set();
}
