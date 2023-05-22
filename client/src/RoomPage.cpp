#include "RoomPage.hpp"
#include "ui_RoomPage.h"
#include "mclineedit.h"

const QString MESSAGE_DELIMITER = ": ";
const QString YOUR_NAME = "You";

RoomPage::RoomPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::RoomPage)
{
    ui->setupUi(this);
    messagesListModel = new QStringListModel(this);
    messagesList = new QStringList();

    membersListModel = new QStringListModel(this);
    membersList = new QStringList();

    socket = new QTcpSocket(this);

    socket->connectToHost(QHostAddress("127.0.0.1"), 1337, QIODevice::ReadWrite);

    socket->write("36 User");

    connect(socket, &QTcpSocket::readyRead, this, &RoomPage::OnGetNewMessage);

    completer = new QCompleter(
        getWordList("../../client/etc/wordlist.txt"), this);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->messageLineEdit->setMultipleCompleter(completer);

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->messageLineEdit, SIGNAL(returnPressed()), ui->sendBtn, SIGNAL(clicked()));

    connect(ui->backBtn, &QAbstractButton::clicked, this, &RoomPage::OnBackButtonClicked);
    connect(ui->sendBtn, &QAbstractButton::clicked, this, &RoomPage::OnSendButtonClicked);
    connect(ui->addUserButton, &QAbstractButton::clicked, this, &RoomPage::OnAddUserButtonClicked);
}

RoomPage::~RoomPage()
{
    delete ui;
    delete messagesList;
    delete membersList;
}

void RoomPage::OnGetNewMessage()
{
    useCase_->GetNewMessage(roomInfo_.id);
}

QString RoomPage::getUserNickname(const std::string& login) {
    QString nickname;
    for (const auto& member : roomInfo_.members)
        if (member.login == login)
            return QString::fromStdString(member.nickname);
}

void RoomPage::ShowRoomInfo(const RoomInfo& roomInfo) {   
    roomInfo_ = roomInfo;
    ui->roomNameLabel->setText(QString::fromStdString(roomInfo.name));
    for (const auto& member : roomInfo.members) {
        membersList->append(QString::fromStdString(member.nickname));
        membersListModel->setStringList(*membersList);
        ui->members->setModel(membersListModel);
    }
}

void RoomPage::ShowSentMessage() {
    messagesList->append(YOUR_NAME + MESSAGE_DELIMITER + tempContent);
    messagesListModel->setStringList(*messagesList);
    ui->listView->setModel(messagesListModel);
}

void RoomPage::ShowAddedUser(const UserInfo& info) {
    roomInfo_.members.push_back(info);
    membersList->append(QString::fromStdString(info.nickname));
    membersListModel->setStringList(*membersList);
    ui->members->setModel(membersListModel);
}

void RoomPage::ShowNewMessage(const Message& message) {
    auto nickname = getUserNickname(message.author);
    auto content = QString::fromStdString(message.content);
    messagesList->append(nickname + MESSAGE_DELIMITER + content);
    messagesListModel->setStringList(*messagesList);
    ui->listView->setModel(messagesListModel);
}

void RoomPage::ShowLastMessages(const std::vector<Message>& messages) {

    timer_->start(3000);

    for (const auto& message : messages) {
        QString nickname;

        if (message.author == userInfo_.login)
            nickname = YOUR_NAME;
        else 
            nickname = getUserNickname(message.author);
        
        auto content = QString::fromStdString(message.content);
        messagesList->append(nickname + MESSAGE_DELIMITER + content);
        messagesListModel->setStringList(*messagesList);
        ui->listView->setModel(messagesListModel);
    }
}

void RoomPage::OnBackButtonClicked() {
    timer_->stop();
    
    messagesList->clear();
    messagesListModel->setStringList(*messagesList);
    ui->listView->setModel(messagesListModel);

    membersList->clear();
    membersListModel->setStringList(*membersList);
    ui->members->setModel(membersListModel);

    controller_->ShowMainPage();
    //close thread
}

void RoomPage::OnSendButtonClicked()
{
    tempContent = ui->messageLineEdit->text();
    Message message;
    message.roomID = roomInfo_.id;
    message.content = tempContent.toStdString();
    message.author = userInfo_.login; 
    ui->messageLineEdit->setText("");
    useCase_->SendMessage(std::move(message));
}

void RoomPage::OnAddUserButtonClicked() {
    auto login = ui->userLineEdit->text();
    if (login.isEmpty())
        ui->errorLabel->setText("Specify user login");
    else {
        useCase_->AddUser(
            roomInfo_.id, login.toStdString()
        );
        ui->userLineEdit->setText("");
        ui->errorLabel->setText("");
    }
}

QStringList RoomPage::getWordList(const QString& path)
{
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

// void RoomPage::ShowOldMessages(const std::vector<Message>& messages){}
// void RoomPage::ShowRoomInfo(const RoomInfo& roomInfo){}
