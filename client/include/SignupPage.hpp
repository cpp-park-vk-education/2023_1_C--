#pragma once
#include <QWidget>
#include "IAccountSwitcher.hpp"
#include "IAccountUseCase.hpp"
#include "IAccountUi.hpp"

namespace Ui {
class SignupPage;
}

class SignupPage : public QWidget,
                   public IAccountUi
{
    Q_OBJECT

public:
    explicit SignupPage(QWidget *parent = nullptr);
    ~SignupPage();

    void ShowError(const std::string& error) override;

    void SetUseCase(IAccountUseCaseSPtr useCase) {
        useCase_ = useCase;
    }
    void SetSwitcher(IAccountSwitcherSPtr switcher) {
        switcher_ = switcher;
    }

public slots:
    void OnSubmitButtonClicked();
    void OnLoginButtonClicked();

private:
    Ui::SignupPage *ui;
    IAccountSwitcherSPtr switcher_;
    IAccountUseCaseSPtr useCase_;
};
