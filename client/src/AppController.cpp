#include "AppController.hpp"
#include "TcpConnection.hpp"

AppController::AppController() {

    accountNetworkSPtr = std::make_shared<AccountNetwork>();
    accountUseCaseSPtr = std::make_shared<AccountUseCase>();

    roomNetworkSPtr = std::make_shared<RoomNetwork>();
    roomUseCaseSPtr = std::make_shared<RoomUseCase>();

    serializerSPtr = std::make_shared<Serializer>();
    deserializerSPtr = std::make_shared<Deserializer>();
    networkManager = std::make_shared<NetworkManager>();

    mainWindow = new MainWindow;

    loginPage = new LoginPage(mainWindow);
    signupPage = new SignupPage(mainWindow);
    mainPage = new MainPage(mainWindow);
    roomPage = new RoomPage(mainWindow);
    roomCreationPage = new RoomCreationPage(mainWindow);
    roomSearchPage = new RoomSearchPage(mainWindow);

    mainPage->SetUseCase(roomUseCaseSPtr);
    mainPage->SetController(mainWindow);

    loginPage->SetUseCase(accountUseCaseSPtr);
    loginPage->SetController(mainWindow);

    signupPage->SetUseCase(accountUseCaseSPtr);
    signupPage->SetController(mainWindow);

    roomPage->SetUseCase(roomUseCaseSPtr);

    roomCreationPage->SetUseCase(roomUseCaseSPtr);
    roomCreationPage->SetController(mainWindow);

    roomSearchPage->SetUseCase(roomUseCaseSPtr);
    roomSearchPage->SetController(mainWindow);

    mainWindow->SetLoginPage(loginPage);
    mainWindow->SetSignupPage(signupPage);
    mainWindow->SetMainPage(mainPage);
    mainWindow->SetRoomPage(roomPage);
    mainWindow->SetRoomCreationPage(roomCreationPage);
    mainWindow->SetRoomSearchPage(roomSearchPage);

    accountUseCaseSPtr->SetLoginPage(loginPage);
    accountUseCaseSPtr->SetSignupPage(signupPage);
    accountUseCaseSPtr->SetRoomUseCase(roomUseCaseSPtr);
    accountUseCaseSPtr->SetNetwork(accountNetworkSPtr);

    accountNetworkSPtr->SetReplyHandler(accountUseCaseSPtr);
    accountNetworkSPtr->SetNetworkManager(networkManager);
    accountNetworkSPtr->SetRequestSerializer(serializerSPtr);
    accountNetworkSPtr->SetResponseSerializer(deserializerSPtr);

    roomUseCaseSPtr->SetRoomNetwork(roomNetworkSPtr);
    roomUseCaseSPtr->SetAccountUseCase(accountUseCaseSPtr);
    roomUseCaseSPtr->SetRoomPage(roomPage);
    roomUseCaseSPtr->SetMainPage(mainPage);
    roomUseCaseSPtr->SetRoomCreationPage(roomCreationPage);
    roomUseCaseSPtr->SetWidgetController(mainWindow);

    roomNetworkSPtr->SetReplyHandler(roomUseCaseSPtr);
    roomNetworkSPtr->SetNetworkManager(networkManager);
    roomNetworkSPtr->SetRequestSerializer(serializerSPtr);
    roomNetworkSPtr->SetResponseSerializer(deserializerSPtr);
    roomNetworkSPtr->SetTcpConnection(std::make_unique<TcpConnection>());
} 

AppController::~AppController() {
    delete mainWindow;
}
