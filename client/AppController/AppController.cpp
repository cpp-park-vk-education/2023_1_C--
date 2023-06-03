#include "AppController.hpp"
#include "TcpConnection.hpp"
#include "NetworkManager.hpp"
#include "Serializer.hpp"
#include "Deserializer.hpp"
#include "HttpRequestCreator.hpp"
#include <QSettings>
#include <QCompleter>
#include <QFile>
#include <QTextStream>

static QStringList getWordList(const QString& path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QStringList fields;
    while(!in.atEnd()) {
        QString line = in.readLine();
        fields.append(line.split(","));
    }
    return fields;
}

AppController::AppController() {
    accountNetworkSPtr = std::make_shared<AccountNetwork>();
    accountUseCaseSPtr = std::make_shared<AccountUseCase>();

    roomNetworkSPtr = std::make_shared<RoomNetwork>();
    roomUseCaseSPtr = std::make_shared<RoomUseCase>();

    auto serializerSPtr = std::make_shared<Serializer>();
    auto deserializerSPtr = std::make_shared<Deserializer>();
    auto networkManager = std::make_shared<NetworkManager>();

    mainWindow = new MainWindow;
    loginPage = new LoginPage(mainWindow);
    signupPage = new SignupPage(mainWindow);
    mainPage = new MainPage(mainWindow);
    roomPage = new RoomPage(mainWindow);
    roomCreationPage = new RoomCreationPage(mainWindow);

    mainPage->SetUseCase(roomUseCaseSPtr);
    mainPage->SetController(mainWindow);

    loginPage->SetUseCase(accountUseCaseSPtr);
    loginPage->SetController(mainWindow);

    signupPage->SetUseCase(accountUseCaseSPtr);
    signupPage->SetController(mainWindow);

    roomPage->SetUseCase(roomUseCaseSPtr);

    roomCreationPage->SetUseCase(roomUseCaseSPtr);

    mainWindow->SetLoginPage(loginPage);
    mainWindow->SetSignupPage(signupPage);
    mainWindow->SetMainPage(mainPage);
    mainWindow->SetRoomPage(roomPage);
    mainWindow->SetRoomCreationPage(roomCreationPage);

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

    auto settings = QSettings("../../client/etc/config.ini", QSettings::IniFormat);
    auto host = settings.value("host").toString().toStdString();
    unsigned short portHttp = settings.value("portHttp").toInt();
    unsigned short portTcp = settings.value("portTcp").toInt();

    HttpRequestCreator requestCreator;
    requestCreator.SetConfiguration(host, portHttp);

    auto requestCreatorSPtr = std::make_shared<HttpRequestCreator>(requestCreator);
    roomNetworkSPtr->SetHttpRequestCreator(requestCreatorSPtr);
    accountNetworkSPtr->SetHttpRequestCreator(requestCreatorSPtr);

    auto tcpConnection = std::make_unique<TcpConnection>();
    tcpConnection->SetConfiguration(host, portTcp);
    roomNetworkSPtr->SetTcpConnection(std::move(tcpConnection));

    auto wordList = getWordList("../../client/etc/wordlist.txt");
    auto usersList = getWordList("../../client/etc/users.txt");
    
#pragma region cringe
    roomPage->SetMessageCompleter(new QCompleter(wordList));
    roomPage->SetUserCompleter(new QCompleter(usersList));

    roomCreationPage->SetWordCompleter(new QCompleter(wordList));
    roomCreationPage->SetUserCompleter(new QCompleter(usersList));
#pragma endregion
} 

AppController::~AppController() {
    delete mainWindow;
}
