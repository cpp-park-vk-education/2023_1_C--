#pragma once
#include "LoginPage.hpp"
#include "SignupPage.hpp"
#include "MainPage.hpp"
#include "RoomPage.hpp"
#include "RoomSearchPage.hpp"
#include "RoomCreationPage.hpp"
#include "IWidgetController.hpp"

class ApplicationUi : public ILoginUi,
                      public ISignupUi,
                      public IRoomPageUi,
                      public IMainPageUi {
public:
    void ShowLoginError(const std::string& error) override;
    void ShowSignupPage() override;
    void ShowSignupError(const std::string& error) override;
    void ShowLoginPage() override;
    void ShowRoomName(const std::string& name) override;
    void ShowNewMessage(const Message& message) override;
    void ShowSentMessage(const Message& message) override;
    void ShowRoomMessages(std::vector<Message> messages) override;
    void ShowMainPage(std::vector<RoomData> rooms) override;
    void ShowRoomSearchPage() override;
    void ShowRoomCreationPage() override;
    
    void SetUserData(const UserData& userData) {
        data = userData;
    }
    void SetLoginPage(LoginPage* page) {
        loginPage = page;
    }
    void SetSignupPage(SignupPage* page) {
        signupPage = page; 
    }
    void SetMainPage(MainPage* page) {
        mainPage = page;
    }
    void SetRoomPage(RoomPage* page) {
        roomPage = page;
    }
    void SetRoomSearchPage(RoomSearchPage* page) {
        roomSearchPage = page;
    }
    void SetRoomCreationPage(RoomCreationPage* page) {
        roomCreationPage = page;
    }
    void SetMain(IWidgetControllerSPtr main) {
        widgetController = main;
    }

private:
    UserData data;
    LoginPage* loginPage;
    SignupPage* signupPage;
    MainPage* mainPage;
    RoomPage* roomPage;
    RoomSearchPage* roomSearchPage;
    RoomCreationPage* roomCreationPage;
    IWidgetControllerSPtr widgetController;
}