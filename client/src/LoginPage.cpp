#include "LoginPage.hpp"
#include "ui_LoginPage.h"
#include "Forms.hpp"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    connect(ui->submitButton, &QPushButton::clicked, this, &LoginPage::OnSubmitButtonClicked);
    connect(ui->signupButton, &QPushButton::clicked, this, &LoginPage::OnSignupButtonClicked);
}

LoginPage::~LoginPage() { 
    delete ui;
}

void LoginPage::ShowError(const std::string& error) {
    ui->errorLabel->setText(QString::fromStdString(error));
}

void LoginPage::OnSignupButtonClicked() {
    controller_->ShowSignupPage();
}

void LoginPage::OnSubmitButtonClicked() {
    auto login = ui->loginLineEdit->text();
    auto password = ui->passwordLineEdit->text();
    LoginForm loginForm(login.toStdString(), password.toStdString());
    useCase_->Login(std::make_unique<LoginForm>(loginForm));
}
