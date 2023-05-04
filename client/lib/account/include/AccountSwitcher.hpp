#include "IAccountSwitcher.hpp"
#include "IWidgetController.hpp"

class AccountSwitcher : public IAccountSwitcher {
public:
    void ShowLoginPage() override;

    void ShowSignupPage() override;
    
    void ShowUserSettingPage() override;

    void SetWidgetController(IWidgetControllerUPtr widgetConroller) {
        widgetConroller_ = std::move(widgetConroller);
    }

private:
    IWidgetControllerUPtr widgetConroller_;
};
