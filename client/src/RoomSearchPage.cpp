#include "RoomSearchPage.hpp"
#include "ui_RoomSearchPage.h"

RoomSearchPage::RoomSearchPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomSearchPage)
{
    ui->setupUi(this);
    connect(ui->searchButton, &QAbstractButton::clicked, this, &RoomSearchPage::SearchRoom);
    connect(ui->backButton, &QAbstractButton::clicked, this, &RoomSearchPage::Back);
}

RoomSearchPage::~RoomSearchPage()
{
    delete ui;
}

void RoomSearchPage::SelectRoom(QListWidgetItem *item) {}

void RoomSearchPage::SearchRoom() {}

void RoomSearchPage::Back() {
    roomSwitcher_->BackOnMainPage();
}

