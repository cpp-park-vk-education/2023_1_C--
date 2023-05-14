#include "MainPage.hpp"
#include "ui_MainPage.h"
#include <algorithm>
#include <optional>
#include <QListWidget>
#include <QAbstractButton>

const int ROOM_ID_ROLE = 1;

MainPage::MainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainPage::SelectRoom);
    connect(ui->selectButton, &QAbstractButton::clicked, this, &MainPage::OnSelectButtonClicked);
}

MainPage::~MainPage()
{
    delete ui;
}

std::optional<RoomData> MainPage::FindRoom(const int roomId) {
    for (auto it = rooms_.begin(); it !=rooms_.end(); ++it)
        if (it->info.id == roomId)
             return *it;
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
    int roomId = item->data(ROOM_ID_ROLE).toInt();
    auto roomData = FindRoom(roomId);
    qDebug() << "Room was found successfully";
    // roomSwitcher_->ShowRoom(roomData.value());
}

void MainPage::OnSelectButtonClicked() {
    QListWidgetItem* item = ui->listWidget->currentItem();
    int roomId = item->data(ROOM_ID_ROLE).toInt();
    auto roomData = FindRoom(roomId);
    qDebug() << "Room was found successfully";
    // roomSwitcher_->ShowRoom(roomData.value());
}
