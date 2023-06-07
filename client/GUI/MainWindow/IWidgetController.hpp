#pragma once
#include <memory>

class IWidgetController {
public:
    virtual ~IWidgetController() {}
    virtual void ShowLoginPage() = 0;
    virtual void ShowSignupPage() = 0;
    virtual void ShowRoomPage() = 0;
    virtual void ShowMainPage() = 0;
    virtual void ShowRoomSearchPage() = 0;
    virtual void ShowRoomCreationPage() = 0;
};

