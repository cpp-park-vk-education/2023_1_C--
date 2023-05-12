#include "IAccountSwitcher.hpp"
#include "IWidgetController.hpp"

class AccountSwitcher : public IAccountSwitcher {
public:
    void ShowLoginPage() override;

    void ShowSignupPage() override;
    
    void ShowUserSettingPage() override;

    void SetWidgetController(IWidgetControllerSPtr widgetConroller) {
        widgetConroller_ = widgetConroller;
    }

private:
    IWidgetControllerSPtr widgetConroller_;
};
