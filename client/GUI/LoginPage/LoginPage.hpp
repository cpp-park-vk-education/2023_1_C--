#pragma once
#include <QWidget>
#include "ILoginPage.hpp"
#include "IWidgetController.hpp"
#include "IAccountUseCase.hpp"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget,
                  public ILoginPage {
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

    void ShowError(const std::string& error) override;

    void SetUseCase(IAccountUseCaseSPtr useCase) {
        useCase_ = useCase;
    }

    void SetController(IWidgetController* controller) {
        controller_ = controller;
    }

private slots:
    void OnSubmitButtonClicked();
    void OnSignupButtonClicked();

private:
    Ui::LoginPage *ui;
    IWidgetController* controller_;
    IAccountUseCaseSPtr useCase_;
};
