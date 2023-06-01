#include "RoomPage.hpp"
#include "ui_RoomPage.h"
#include "mclineedit.h"

const QString MESSAGE_DELIMITER = ": ";
const QString YOUR_NAME = "You";

RoomPage::RoomPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::RoomPage) {
    ui->setupUi(this);

    messagesListModel = new QStringListModel(this);
    messagesList = new QStringList();

    membersListModel = new QStringListModel(this);
    membersList = new QStringList();

    messageCompleter = new QCompleter(getWordList("../../client/etc/wordlist.txt"), this);
    messageCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->messageLineEdit->setMultipleCompleter(messageCompleter);
    // connect(ui->messageLineEdit, SIGNAL(returnPressed()), ui->sendBtn, SIGNAL(clicked()));

    userCompleter = new QCompleter(getWordList("../../client/etc/users.txt"), this);
    userCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->userLineEdit->setMultipleCompleter(userCompleter);
    // connect(ui->userLineEdit, &QLineEdit::returnPressed, ui->addUserButton, &QPushButton::clicked);

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->backBtn, &QAbstractButton::clicked, this, &RoomPage::OnBackButtonClicked);
    connect(ui->sendBtn, &QAbstractButton::clicked, this, &RoomPage::OnSendButtonClicked);
    connect(ui->addUserButton, &QAbstractButton::clicked, this, &RoomPage::OnAddUserButtonClicked);

    ui->membersListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

RoomPage::~RoomPage() {
    delete ui;
    delete messagesList;
    delete membersList;
}

void RoomPage::ShowRoomInfo(const RoomInfo& roomInfo) {   
    roomInfo_ = roomInfo;
    ui->roomNameLabel->setText(QString::fromStdString(roomInfo.name));
    for (const auto& member : roomInfo.members) {
        members.insert(QString::fromStdString(member.login),
                       QString::fromStdString(member.nickname)); // {member.login, member.info}
        membersList->append(QString::fromStdString(member.nickname));
        membersListModel->setStringList(*membersList);
        ui->membersListView->setModel(membersListModel);
    }
}

void RoomPage::ShowLastMessages(const std::vector<Message>& messages) {
    for (const auto& message : messages) {
        QString nickname;
        if (message.author == userInfo_.login)
            nickname = YOUR_NAME;
        else 
            nickname = members.value(QString::fromStdString(message.author));
        auto content = QString::fromStdString(message.content);
        messagesList->append(nickname + MESSAGE_DELIMITER + content);
        messagesListModel->setStringList(*messagesList);
        ui->listView->setModel(messagesListModel);
    }
}

void RoomPage::ShowSentMessage() {
    ui->messageLineEdit->setText("");
    ui->roomErrorLabel->setText("");

    messagesList->append(YOUR_NAME + MESSAGE_DELIMITER + tempContent);
    messagesListModel->setStringList(*messagesList);
    ui->listView->setModel(messagesListModel);
}

void RoomPage::ShowAddedUser(const UserInfo& info) {
    ui->userLineEdit->setText("");
    ui->userErrorLabel->setText("");
    roomInfo_.members.push_back(info);
    membersList->append(QString::fromStdString(info.nickname));
    membersListModel->setStringList(*membersList);
    ui->membersListView->setModel(membersListModel);
}

void RoomPage::ShowNewMessage(const Message& message) {
    auto nickname = members.value(QString::fromStdString(message.author));
    auto content = QString::fromStdString(message.content);
    messagesList->append(nickname + MESSAGE_DELIMITER + content);
    messagesListModel->setStringList(*messagesList);
    ui->listView->setModel(messagesListModel);
}

void RoomPage::OnBackButtonClicked() {
    ClearPage();
    useCase_->ShowMainPage();
}

void RoomPage::OnSendButtonClicked() {
    tempContent = ui->messageLineEdit->text();
    Message message;
    message.roomID = roomInfo_.id;
    message.content = tempContent.toStdString();
    message.author = userInfo_.login; 
    ui->messageLineEdit->setText("");
    useCase_->SendMessage(std::move(message));
}

void RoomPage::OnAddUserButtonClicked() {
    ui->userErrorLabel->setText("");
    ui->roomErrorLabel->setText("");
    auto login = ui->userLineEdit->text();
    if (login.isEmpty())
        ui->userErrorLabel->setText("Specify user login");
    else
        useCase_->AddUser(roomInfo_.id, login.toStdString());
}

QStringList RoomPage::getWordList(const QString& path) {
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

void RoomPage::ShowError(const std::string& error) {
    ui->roomErrorLabel->setText(QString::fromStdString(error));
}

void RoomPage::ClearPage() {
    ui->userErrorLabel->setText("");
    ui->roomErrorLabel->setText("");

    ui->userLineEdit->setText("");
    ui->messageLineEdit->setText("");

    messagesList->clear();
    messagesListModel->setStringList(*messagesList);
    ui->listView->setModel(messagesListModel);

    membersList->clear();
    membersListModel->setStringList(*membersList);
    ui->membersListView->setModel(membersListModel);
}
