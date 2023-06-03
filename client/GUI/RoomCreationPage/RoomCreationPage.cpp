#include "RoomCreationPage.hpp"
#include "ui_RoomCreationPage.h"
#include <QStringListModel>

RoomCreationPage::RoomCreationPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::RoomCreationPage) {
    ui->setupUi(this);

    completer = new QCompleter(this);
    userCompleter = new QCompleter(this);

    connect(ui->createButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnCreateRoomButtonClicked);
    connect(ui->backButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnBackButtonClicked);
    connect(ui->addButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnAddUserButtonClicked);
}

RoomCreationPage::~RoomCreationPage()
{
    delete ui;
}

void RoomCreationPage::SetWordCompleter(const QStringList& wordsList) {
    completer->setModel(new QStringListModel(wordsList, completer));
    ui->name->setMultipleCompleter(completer);
}

void RoomCreationPage::SetUserCompleter(const QStringList& usersList) {
    userCompleter->setModel(new QStringListModel(usersList, userCompleter));
    ui->username->setMultipleCompleter(userCompleter);
}

void RoomCreationPage::OnAddUserButtonClicked() {
    if (ui->username->text().isEmpty()) {
        ui->errorLabel->setText("Specify the user login");
        return;
    }
    members.push_back(ui->username->text());
    ui->members->addItem(ui->username->text());
    ui->username->setText("");
}

void RoomCreationPage::OnBackButtonClicked() {
    roomUseCase_->ShowMainPage();
    clearPage();
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
    
    auto name = ui->name->text().toStdString();

    std::vector<std::string> stdMembers;
    for (const auto& member : members)
        stdMembers.push_back(member.toStdString());

    roomUseCase_->CreateRoom(std::move(name), std::move(stdMembers));
    clearPage();
}

void RoomCreationPage::ShowError(const std::string& error) {
    ui->errorLabel->setText(QString::fromStdString(error));
}


void RoomCreationPage::clearPage() {
    members.clear();
    ui->members->clear();
    ui->name->setText("");
    ui->username->setText("");
}