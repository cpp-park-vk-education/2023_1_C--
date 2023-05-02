#pragma once
#include <memory>

class IWidgetController {
public:
    virtual ~IWidgetController() {}
    virtual void ShowLoginPage() = 0;
    virtual void ShowSignupPage() = 0;
    virtual void ShowUserSettingPage() = 0;
    virtual void ShowRoomPage() = 0;
    virtual void ShowAllRoomsPage() = 0;
};

using IWidgetControllerUPtr = std::unique_ptr<IWidgetController>;
