#include "AppController.hpp"

AppController::AppController() {
    accountNetworkSPtr = std::make_shared<AccountNetwork>();
    accountReplyHandlerSPtr = std::make_shared<AccountReplyHandler>();
    accountSwitcherSPtr = std::make_shared<AccountSwitcher>();
    accountUseCaseSPtr = std::make_shared<AccountUseCase>();

    roomNetworkSPtr = std::make_shared<RoomNetwork>();
    roomReplyHandlerSPtr = std::make_shared<RoomReplyHandler>();
    roomSwitcherSPtr = std::make_shared<RoomSwitcher>();
    roomUseCaseSPtr = std::make_shared<RoomUseCase>();

    serializerSPtr = std::make_shared<Serializer>();
    deserializerSPtr = std::make_shared<Deserializer>();

    networkManager = new NetworkManager;

    loginPage = new LoginPage;
    mainPage = new MainPage;

    mainWindow = new MainWindow;
    mainWindow->SetLoginPage(loginPage);
    mainWindow->SetMainPage(mainPage);

    loginPage->SetUseCase(accountUseCaseSPtr);
    
    accountUseCaseSPtr->SetAccountUi(loginPage);
    accountUseCaseSPtr->SetNetwork(accountNetworkSPtr);

    accountNetworkSPtr->SetReplyHandler(accountReplyHandlerSPtr);
    accountNetworkSPtr->SetNetworkManager(networkManager);
    accountNetworkSPtr->SetRequestSerializer(serializerSPtr);
    accountNetworkSPtr->SetResponseSerializer(deserializerSPtr);

    accountReplyHandlerSPtr->SetRoomSwitcher(roomSwitcherSPtr);
    accountReplyHandlerSPtr->SetAccountUi(loginPage);

    // roomUseCaseSPtr->SetRoomPageUi();
    roomUseCaseSPtr->SetMainPageUi(mainPage);
    roomUseCaseSPtr->SetRoomNetwork(roomNetworkSPtr);
    
    roomNetworkSPtr->SetReplyHandler(roomReplyHandlerSPtr);
    roomNetworkSPtr->SetNetworkManager(networkManager);
    roomNetworkSPtr->SetRequestSerializer(serializerSPtr);
    roomNetworkSPtr->SetResponseSerializer(deserializerSPtr);
    
    roomReplyHandlerSPtr->SetRoomSwitcher(roomSwitcherSPtr);

    roomSwitcherSPtr->SetWidgetController(mainWindow);
    roomSwitcherSPtr->SetMainPageUi(mainPage);

} 

AppController::~AppController() {
    delete mainWindow;
    delete networkManager;
    // delete loginPage;
    // delete mainPage;
}