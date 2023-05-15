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
    signupPage = new SignupPage;
    mainPage = new MainPage;
    roomPage = new RoomPage;
    roomCreationPage = new RoomCreationPage;
    roomSearchPage = new RoomSearchPage;

    mainWindow = new MainWindow;
    mainWindow->SetLoginPage(loginPage);
    mainWindow->SetSignupPage(signupPage);
    mainWindow->SetMainPage(mainPage);
    mainWindow->SetRoomPage(roomPage);
    mainWindow->SetRoomCreationPage(roomCreationPage);
    mainWindow->SetRoomSearchPage(roomSearchPage);

    loginPage->SetUseCase(accountUseCaseSPtr);
    loginPage->SetSwitcher(accountSwitcherSPtr);

    signupPage->SetUseCase(accountUseCaseSPtr);
    signupPage->SetSwitcher(accountSwitcherSPtr);

    mainPage->SetRoomSwitcher(roomSwitcherSPtr);
    roomPage->SetRoomSwitcher(roomSwitcherSPtr);

    roomCreationPage->SetRoomSwitcher(roomSwitcherSPtr);
    roomCreationPage->SetRoomUseCase(roomUseCaseSPtr);

    roomSearchPage->SetRoomSwitcher(roomSwitcherSPtr);
    roomSearchPage->SetRoomUseCase(roomUseCaseSPtr);
    
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
    accountSwitcherSPtr->SetWidgetController(mainWindow);
    
    roomSwitcherSPtr->SetWidgetController(mainWindow);
    roomSwitcherSPtr->SetMainPageUi(mainPage);

} 

AppController::~AppController() {
    delete mainWindow;
    delete networkManager;
    // delete loginPage;
    // delete mainPage;
    // delete roomPage
    // delete roomCreationPage
    // delete roomSearchPage
}
