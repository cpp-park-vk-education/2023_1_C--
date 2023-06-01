#pragma once
#include "AccountNetwork.hpp"
#include "AccountUseCase.hpp"
#include "RoomNetwork.hpp"
#include "RoomUseCase.hpp"
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
    std::shared_ptr<AccountUseCase> accountUseCaseSPtr;
    std::shared_ptr<RoomNetwork> roomNetworkSPtr;
    std::shared_ptr<RoomUseCase> roomUseCaseSPtr;
    std::shared_ptr<Serializer> serializerSPtr;
    std::shared_ptr<Deserializer> deserializerSPtr;
    std::shared_ptr<NetworkManager> networkManager;
    LoginPage* loginPage;
    SignupPage* signupPage;
    MainPage* mainPage;
    RoomPage* roomPage;
    RoomCreationPage* roomCreationPage;
};
