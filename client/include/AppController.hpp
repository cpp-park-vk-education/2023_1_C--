#pragma once
#include "AccountNetwork.hpp"
#include "AccountReplyHandler.hpp"
#include "AccountSwitcher.hpp"
#include "AccountUseCase.hpp"

#include "RoomNetwork.hpp"
#include "RoomReplyHandler.hpp"
#include "RoomSwitcher.hpp"
#include "RoomUseCase.hpp"

#include "RoomPage.hpp"
#include "MainWindow.hpp"

#include "NetworkManager.hpp"
#include "Serializer.hpp"
#include "Deserializer.hpp"
#include <memory>

class AppController {
public:
    AppController();
    ~AppController();

    MainWindow* mainWindow;

private:
    std::shared_ptr<AccountNetwork> accountNetworkSPtr; 
    std::shared_ptr<AccountReplyHandler> accountReplyHandlerSPtr;
    std::shared_ptr<AccountSwitcher> accountSwitcherSPtr;
    std::shared_ptr<AccountUseCase> accountUseCaseSPtr;

    std::shared_ptr<RoomNetwork> roomNetworkSPtr;
    std::shared_ptr<RoomReplyHandler> roomReplyHandlerSPtr;
    std::shared_ptr<RoomSwitcher> roomSwitcherSPtr;
    std::shared_ptr<RoomUseCase> roomUseCaseSPtr;
    
    std::shared_ptr<Serializer> serializerSPtr;
    std::shared_ptr<Deserializer> deserializerSPtr;    
    NetworkManager* networkManager;

    LoginPage* loginPage;
    SignupPage* signupPage;
    MainPage* mainPage;
    RoomPage* roomPage;
    RoomCreationPage* roomCreationPage;
    RoomSearchPage* roomSearchPage;

};
