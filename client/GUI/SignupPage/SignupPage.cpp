#include "SignupPage.hpp"
#include "ui_SignupPage.h"
#include "Forms.hpp"

SignupPage::SignupPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupPage)
{
    ui->setupUi(this);
    connect(ui->submitButton, &QPushButton::clicked, this, &SignupPage::OnSubmitButtonClicked);
    connect(ui->loginButton, &QPushButton::clicked, this, &SignupPage::OnLoginButtonClicked);
}

SignupPage::~SignupPage()
{
    delete ui;
}

void SignupPage::ShowError(const std::string& error) {
    ui->errorLabel->setText(QString::fromStdString(error));
}

void SignupPage::OnLoginButtonClicked() {
    controller_->ShowLoginPage();
}

void SignupPage::OnSubmitButtonClicked() {
    auto login = ui->loginLineEdit->text();
    auto password = ui->passwordLineEdit->text();
    auto nickname = ui->nicknameLineEdit->text();
    auto repeatedPassword = ui->repeatedPasswordLineEdit->text();
    SignupForm signupForm(login.toStdString(),
                          nickname.toStdString(),
                          password.toStdString(),
                          repeatedPassword.toStdString());
    signupForm.SetFirstname(ui->firstnameLineEdit->text().toStdString());
    signupForm.SetLastname(ui->lastnameLineEdit->text().toStdString());
    useCase_->Signup(std::make_unique<SignupForm>(signupForm));
}
