#include "ApplicationUi.hpp"    

void ApplicationUi::ShowLoginError(const std::string& error) {}
void ApplicationUi::ShowSignupPage() {
    widgetController
}
void ApplicationUi::ShowSignupError(const std::string& error) {}
void ApplicationUi::ShowLoginPage() {}
void ApplicationUi::ShowRoomName(const std::string& name) {}
void ApplicationUi::ShowNewMessage(const Message& message) {}
void ApplicationUi::ShowSentMessage(const Message& message) {}
void ApplicationUi::ShowRoomMessages(std::vector<Message> messages) {}
void ApplicationUi::ShowMainPage(std::vector<RoomData> rooms) {}
void ApplicationUi::ShowRoomSearchPage() {}
void ApplicationUi::ShowRoomCreationPage() {}

void ApplicationUi::SetLoginPage(LoginPage* page) {}
void ApplicationUi::SetSignupPage(SignupPage* page) {}
void ApplicationUi::SetMainPage(MainPage* page) {}
void ApplicationUi::SetRoomPage(RoomPage* page) {}
void ApplicationUi::SetRoomSearchPage(RoomSearchPage* page) {}
void ApplicationUi::SetRoomCreationPage(RoomCreationPage* page) {}
