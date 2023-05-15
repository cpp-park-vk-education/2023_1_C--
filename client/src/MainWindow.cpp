#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetLoginPage(LoginPage* loginPage) {
    loginPage_ = loginPage; 
    ui->stackedWidget->addWidget(loginPage_);
}

void MainWindow::SetMainPage(MainPage* mainPage) {
    mainPage_ = mainPage; 
    ui->stackedWidget->addWidget(mainPage_);
}

void MainWindow::SetRoomPage(RoomPage* roomPage){
    roomPage_ = roomPage;
    ui->stackedWidget->addWidget(roomPage_);
}

void MainWindow::ShowLoginPage() {
    ui->stackedWidget->setCurrentWidget(loginPage_);
}

// void MainWindow::ShowSignupPage() {}
// void MainWindow::ShowUserSettingPage() {}

void MainWindow::ShowRoomPage() {
    ui->stackedWidget->setCurrentWidget(roomPage_);
}

void MainWindow::ShowMainPage() {
    ui->stackedWidget->setCurrentWidget(mainPage_);
}
void MainWindow::ShowRoomInfo() {}
