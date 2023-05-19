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

void MainWindow::SetLoginPage(LoginPage* page) {
    loginPageIndex = ui->stackedWidget->addWidget(page);
}

void MainWindow::SetSignupPage(SignupPage* page) {
    signupPageIndex = ui->stackedWidget->addWidget(page);
}

void MainWindow::SetMainPage(MainPage* page) {
    mainPageIndex = ui->stackedWidget->addWidget(page);
}

void MainWindow::SetRoomPage(RoomPage* page) {
    roomPageIndex = ui->stackedWidget->addWidget(page);
}

void MainWindow::SetRoomSearchPage(RoomSearchPage* page) {
    roomSearchPageIndex = ui->stackedWidget->addWidget(page);
}

void MainWindow::SetRoomCreationPage(RoomCreationPage* page) {
    roomCreationPageIndex = ui->stackedWidget->addWidget(page);
}

void MainWindow::ShowLoginPage() {
    ui->stackedWidget->setCurrentIndex(loginPageIndex);
}

void MainWindow::ShowSignupPage() {
    ui->stackedWidget->setCurrentIndex(signupPageIndex);
}

void MainWindow::ShowRoomPage() {
    ui->stackedWidget->setCurrentIndex(roomPageIndex);
}

void MainWindow::ShowMainPage() {
    ui->stackedWidget->setCurrentIndex(mainPageIndex);
}

void MainWindow::ShowRoomSearchPage() {
    ui->stackedWidget->setCurrentIndex(roomSearchPageIndex);
}

void MainWindow::ShowRoomCreationPage() {
    ui->stackedWidget->setCurrentIndex(roomCreationPageIndex);
}
