#include "RoomCreationPage.hpp"
#include "ui_RoomCreationPage.h"

RoomCreationPage::RoomCreationPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomCreationPage)
{
    ui->setupUi(this);
    connect(ui->createButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnCreateRoomButtonClicked);
    connect(ui->backButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnBackButtonClicked);
    connect(ui->addButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnAddUserButtonClicked);
}

RoomCreationPage::~RoomCreationPage()
{
    delete ui;
}

void RoomCreationPage::OnAddUserButtonClicked() {
    if (ui->username->text().isEmpty()) {
        ui->errorLabel->setText("Specify the user login");
        return;
    }
    members.push_back(ui->username->text().toStdString());
    ui->members->addItem(ui->username->text());
    ui->username->setText(""); 
}

void RoomCreationPage::OnBackButtonClicked() {
    controller_->ShowMainPage();
}

void RoomCreationPage::OnCreateRoomButtonClicked() {    
    if(ui->name->text().isEmpty()) {
        ui->errorLabel->setText("Name is required");
        return;
    }
    
    if(members.empty()) {
        ui->errorLabel->setText("Add user to room");
        return;
    }

    RoomInfo roomInfo;
    roomInfo.name = ui->name->text().toStdString();
    roomInfo.members = members;
    roomUseCase_->CreateRoom(std::move(roomInfo));
}