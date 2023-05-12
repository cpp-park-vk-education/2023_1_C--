#pragma once
#include "AccountNetwork.hpp"
#include "AccountReplyHandler.hpp"
#include "AccountSwitcher.hpp"
#include "AccountUseCase.hpp"
// #include "AccountUi.hpp"
#include "RoomNetwork.hpp"
#include "RoomReplyHandler.hpp"
#include "RoomSwitcher.hpp"
#include "RoomUseCase.hpp"
// #include "RoomUi.hpp"

class AppController {
public:
    AppController();
    ~AppController() {}

private:
    AccountNetwork accountNetwork; 
    AccountReplyHandler accountReplyHandler;
    AccountSwitcher accountSwitcher;
    AccountUseCase accountUseCase;
    // AccountUi accountUi;
    RoomNetwork roomNetwork;
    RoomReplyHandler roomReplyHandler;
    RoomSwitcher roomSwitcher;
    RoomUseCase roomUseCase;
    // RoomUi roomUi;
};
