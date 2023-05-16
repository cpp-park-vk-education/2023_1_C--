#pragma once
#include <QWidget>
#include "AccountUseCase.hpp"
#include "AccountSwitcher.hpp"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget, 
                  public IAccountUi
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

    void ShowError(const std::string& error) override;

    void SetUseCase(IAccountUseCaseSPtr useCase) {
        useCase_ = useCase;
    }

    void SetSwitcher(IAccountSwitcherSPtr switcher) {
        switcher_ = switcher;
    }

private slots:
    void OnSubmitButtonClicked();
    void OnSignupButtonClicked();

private:
    Ui::LoginPage *ui;
    IAccountUseCaseSPtr useCase_;
    IAccountSwitcherSPtr switcher_;
};
