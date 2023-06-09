#include "MainPage.hpp"
#include "ui_MainPage.h"
#include <QListWidget>
#include <QAbstractButton>

const int ROOM_ID_ROLE = 1;

MainPage::MainPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainPage) {
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemActivated, this, &MainPage::OnSelectRoom);
    connect(ui->createButton, &QAbstractButton::clicked, this, &MainPage::OnCreateRoom);
    connect(ui->refreshButton, &QAbstractButton::clicked, this, &MainPage::OnRefreshMainPage);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::ShowRooms(const Rooms& rooms) {
    ui->errorLabel->setText("");
    ui->listWidget->clear();
    for(auto it = rooms.begin(); it != rooms.end(); ++it) {
        auto roomListWidget = new QListWidgetItem(ui->listWidget);
        roomListWidget->setText(QString::fromStdString(it->second.name));
        roomListWidget->setData(ROOM_ID_ROLE, it->first);
        ui->listWidget->addItem(roomListWidget);
    }
    ui->listWidget->sortItems();
}

void MainPage::ShowError(const std::string& error) {
    ui->errorLabel->setText(QString::fromStdString(error));
}

void MainPage::OnSelectRoom(QListWidgetItem *item) {
    ui->errorLabel->setText("");
    const int roomID = item->data(ROOM_ID_ROLE).toString().toInt();
    useCase_->GetRoomMessages(roomID);
}

void MainPage::OnCreateRoom() {
    controller_->ShowRoomCreationPage();
}

void MainPage::OnRefreshMainPage() {
    useCase_->RefreshMainPage();
}
