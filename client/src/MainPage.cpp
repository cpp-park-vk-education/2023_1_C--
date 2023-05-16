#include "MainPage.hpp"
#include "ui_MainPage.h"
#include <algorithm>
#include <QListWidget>
#include <QAbstractButton>

const int ROOM_ID_ROLE = 1;

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainPage::SelectRoom);
    connect(ui->searchButton, &QAbstractButton::clicked, this, &MainPage::SearchRoom);
    connect(ui->createButton, &QAbstractButton::clicked, this, &MainPage::CreateRoom);
    connect(ui->searchButton, &QAbstractButton::clicked, ui->listWidget, &QListWidget::clear);
    connect(ui->createButton, &QAbstractButton::clicked, ui->listWidget, &QListWidget::clear);
}

MainPage::~MainPage()
{
    delete ui;
}
void MainPage::ShowRoomSearchPage() {
    roomSwitcher_->ShowRoomSearchPage();
}

void MainPage::ShowRoomCreationPage() {
    roomSwitcher_->ShowRoomCreationPage();
}


std::optional<RoomData> MainPage::FindRoom(const int roomId) {
    for (const auto room : rooms_)
        if (room.info.id == roomId)
             return room;
    return std::nullopt;
}

void MainPage::ShowMainPage(std::vector<RoomData> rooms) {
    rooms_ = std::move(rooms);
    for_each(rooms_.begin(), rooms_.end(), [this](const RoomData& room) {
        QListWidgetItem* roomWidget = new QListWidgetItem(ui->listWidget);
        roomWidget->setText(QString::fromStdString(room.info.name));
        roomWidget->setData(ROOM_ID_ROLE, room.info.id);
        ui->listWidget->addItem(roomWidget);
    });
}

void MainPage::SelectRoom(QListWidgetItem *item) {
    const int roomId = item->data(ROOM_ID_ROLE).toString().toInt();
    auto roomData = FindRoom(roomId);
    if (roomData)
        roomSwitcher_->ShowRoom(roomData.value());
}
