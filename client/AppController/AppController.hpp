#pragma once
#include "AccountNetwork.hpp"
#include "AccountUseCase.hpp"
#include "RoomNetwork.hpp"
#include "RoomUseCase.hpp"
#include "MainWindow.hpp"

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
    LoginPage* loginPage;
    SignupPage* signupPage;
    MainPage* mainPage;
    RoomPage* roomPage;
    RoomCreationPage* roomCreationPage;
};
