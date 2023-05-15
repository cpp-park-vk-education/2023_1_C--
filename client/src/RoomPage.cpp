#include "RoomPage.hpp"
#include "ui_RoomPage.h"

RoomPage::RoomPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomPage)
{
    ui->setupUi(this);
}

RoomPage::~RoomPage()
{
    delete ui;
}
