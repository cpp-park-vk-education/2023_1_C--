#include "AppController.hpp"

AppController::AppController() {
    accountNetworkSPtr = std::make_shared<AccountNetwork>();
    accountSwitcherSPtr = std::make_shared<AccountSwitcher>();
    accountUseCaseSPtr = std::make_shared<AccountUseCase>();

    roomNetworkSPtr = std::make_shared<RoomNetwork>();
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

    roomPage->SetRoomUseCase(roomUseCaseSPtr);
    roomPage->SetRoomSwitcher(roomSwitcherSPtr);
    // roomPage->SetRoomUseCase(roomUseCaseSPtr);

    roomCreationPage->SetRoomSwitcher(roomSwitcherSPtr);
    roomCreationPage->SetRoomUseCase(roomUseCaseSPtr);

    roomSearchPage->SetRoomSwitcher(roomSwitcherSPtr);
    roomSearchPage->SetRoomUseCase(roomUseCaseSPtr);
    
    accountUseCaseSPtr->SetUi(loginPage);
    accountUseCaseSPtr->SetNetwork(accountNetworkSPtr);

    accountNetworkSPtr->SetReplyHandler(accountUseCaseSPtr);
    accountNetworkSPtr->SetNetworkManager(networkManager);
    accountNetworkSPtr->SetRequestSerializer(serializerSPtr);
    accountNetworkSPtr->SetResponseSerializer(deserializerSPtr);

    // roomUseCaseSPtr->SetRoomPageUi();
    roomUseCaseSPtr->SetMainPageUi(mainPage);
    roomUseCaseSPtr->SetRoomNetwork(roomNetworkSPtr);
    
    roomNetworkSPtr->SetReplyHandler(roomUseCaseSPtr);
    roomNetworkSPtr->SetNetworkManager(networkManager);
    roomNetworkSPtr->SetRequestSerializer(serializerSPtr);
    roomNetworkSPtr->SetResponseSerializer(deserializerSPtr);
    
    accountSwitcherSPtr->SetWidgetController(mainWindow);
    
    roomSwitcherSPtr->SetWidgetController(mainWindow);
    roomSwitcherSPtr->SetMainPageUi(mainPage);
    roomSwitcherSPtr->SetRoomPageUi(roomPage);

} 

AppController::~AppController() {
    delete networkManager;

    delete loginPage;
    delete mainPage;
    delete roomPage;
    delete roomCreationPage;
    delete roomSearchPage;
    delete mainWindow;
}
