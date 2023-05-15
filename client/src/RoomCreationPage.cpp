#include "RoomCreationPage.hpp"
#include "ui_RoomCreationPage.h"
#include <QList>

RoomCreationPage::RoomCreationPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomCreationPage)
{
    ui->setupUi(this);
    connect(ui->createButton, &QAbstractButton::clicked, this, &RoomCreationPage::CreateRoom);
    connect(ui->backButton, &QAbstractButton::clicked, this, &RoomCreationPage::Back);
    connect(ui->addButton, &QAbstractButton::clicked, this, &RoomCreationPage::AddUser);

}

RoomCreationPage::~RoomCreationPage()
{
    delete ui;
}

void RoomCreationPage::CreateRoom() {
    RoomInfo roomInfo;
    roomInfo.name = ui->name->text().toStdString();
    roomInfo.members = members;
    roomUseCase_->CreateRoom(roomInfo);
}

void RoomCreationPage::AddUser() {
    members.push_back(ui->username->text().toStdString());
    ui->members->addItem(ui->username->text());
    ui->username->setText(""); 
}

void RoomCreationPage::Back() {
    roomSwitcher_->BackOnMainPage();
}
