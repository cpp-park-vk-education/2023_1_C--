#include "RoomCreationPage.hpp"
#include "ui_RoomCreationPage.h"
#include <QString>

RoomCreationPage::RoomCreationPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomCreationPage)
{
    ui->setupUi(this);
    connect(ui->createButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnCreateRoomButtonClicked);
    connect(ui->backButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnBackButtonClicked);
    connect(ui->addButton, &QAbstractButton::clicked, this, &RoomCreationPage::OnAddUserButtonClicked);

    userCompleter = new QCompleter(getWordList("../../client/etc/users.txt"), this);
    userCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->username->setMultipleCompleter(userCompleter);

    nameCompleter = new QCompleter(getWordList("../../client/etc/wordlist.txt"), this);
    nameCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->name->setMultipleCompleter(nameCompleter);

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
    ClearForm();
    roomUseCase_->ShowMainPage();
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
    roomUseCase_->CreateRoom(std::move(name), std::move(members));
    ClearForm();
}

void RoomCreationPage::ClearForm() {
    members.clear();
    ui->members->clear();
    ui->name->setText("");
    ui->username->setText("");
}

void RoomCreationPage::ShowError(const std::string& error) {
    ui->errorLabel->setText(QString::fromStdString(error));
}

QStringList RoomCreationPage::getWordList(const QString& path) {
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QStringList fields;
    while(!in.atEnd()) {
        QString line = in.readLine();
        fields.append(line.split(","));
    }
    return fields;
}
