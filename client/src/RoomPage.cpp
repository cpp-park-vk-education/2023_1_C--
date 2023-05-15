#include "RoomPage.hpp"
#include "ui_RoomPage.h"

RoomPage::RoomPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::RoomPage)
{
    ui->setupUi(this);
//    connect(ui->pushButton, &QPushButton::clicked, this, &LoginPage::OnSubmitButtonClicked);
}

RoomPage::~RoomPage()
{
    delete ui;
}

void RoomPage::ShowRoomInfo(const RoomInfo& roomInfo){}
void RoomPage::ShowRoomName(const std::string& name){}
void RoomPage::ShowLastMessages(const std::vector<Message>& messages){}
void RoomPage::ShowOldMessages(const std::vector<Message>& messages) {}
