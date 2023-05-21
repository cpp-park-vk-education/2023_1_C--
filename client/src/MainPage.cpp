#include "MainPage.hpp"
#include "ui_MainPage.h"
#include <QListWidget>
#include <QAbstractButton>

const int ROOM_ID_ROLE = 1;

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainPage::OnSelectRoom);
    connect(ui->searchButton, &QAbstractButton::clicked, this, &MainPage::OnSearchRoom);
    connect(ui->createButton, &QAbstractButton::clicked, this, &MainPage::OnCreateRoom);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::ShowRooms(const std::vector<RoomInfo>& rooms) {
    ui->listWidget->clear();
    for(const auto& room : rooms) {
        QListWidgetItem* roomWidget = new QListWidgetItem(ui->listWidget);
        roomWidget->setText(QString::fromStdString(room.name));
        roomWidget->setData(ROOM_ID_ROLE, room.id);
        ui->listWidget->addItem(roomWidget);
    }
}

void MainPage::OnSelectRoom(QListWidgetItem *item) {
    const int roomID = item->data(ROOM_ID_ROLE).toString().toInt();
    useCase_->GetRoomMessages(roomID);
}

void MainPage::OnCreateRoom() {
    controller_->ShowRoomCreationPage();
}

void MainPage::OnSearchRoom() {
    controller_->ShowRoomSearchPage();
}

