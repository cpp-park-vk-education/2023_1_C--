#pragma once
#include <QWidget>
#include "ISignupPage.hpp"
#include "IWidgetController.hpp"
#include "IAccountUseCase.hpp"

namespace Ui {
class SignupPage;
}

class SignupPage : public QWidget,
                   public ISignupPage
{
    Q_OBJECT

public:
    explicit SignupPage(QWidget *parent = nullptr);
    ~SignupPage();

    void ShowError(const std::string& error) override;

    void SetUseCase(IAccountUseCaseSPtr useCase) {
        useCase_ = useCase;
    }
    
    void SetController(IWidgetController* controller) {
        controller_ = controller;
    }

private slots:
    void OnSubmitButtonClicked();
    void OnLoginButtonClicked();

private:
    Ui::SignupPage *ui;
    IAccountUseCaseSPtr useCase_;
    IWidgetController* controller_;
};
