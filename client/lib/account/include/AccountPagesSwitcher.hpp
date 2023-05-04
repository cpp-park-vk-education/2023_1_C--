#include "IAccountPagesSwitcher.hpp"
#include "IWidgetController.hpp"

class AccountPagesSwitcher : public IAccountPagesSwitcher {
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
