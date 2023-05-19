#include "RoomSearchPage.hpp"
#include "ui_RoomSearchPage.h"

RoomSearchPage::RoomSearchPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomSearchPage)
{
    ui->setupUi(this);
    connect(ui->searchButton, &QAbstractButton::clicked, this, &RoomSearchPage::OnSearchButtonClicked);
    connect(ui->backButton, &QAbstractButton::clicked, this, &RoomSearchPage::OnBackButtonClicked);
}

RoomSearchPage::~RoomSearchPage()
{
    delete ui;
}

void RoomSearchPage::OnSelectRoom(QListWidgetItem *item) {}

void RoomSearchPage::OnSearchButtonClicked() {}

void RoomSearchPage::OnBackButtonClicked() {
    // roomSwitcher_->BackOnMainPage();
}

