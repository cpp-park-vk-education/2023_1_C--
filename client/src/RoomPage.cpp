#include "RoomPage.hpp"
#include "ui_RoomPage.h"
#include "MCLineEdit.hpp"

RoomPage::RoomPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::RoomPage)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    list = new QStringList();
    auto timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(OnGetNewMessage()));
    timer->start(1000);

    completer = new QCompleter(
        getWordList("../../client/etc/wordlist.txt"), this);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->messageLineEdit->setMultipleCompleter(completer);

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->messageLineEdit, SIGNAL(returnPressed()), ui->sendBtn, SIGNAL(clicked()));
}

RoomPage::~RoomPage()
{
    delete ui;
    delete list;
}

void RoomPage::OnGetNewMessage()
{
    useCase_->GetNewMessage(roomInfo_.id);
}


void RoomPage::ShowRoomName(const std::string& name){
    ui->roomNameLabel->setText(QString::fromStdString(name));
}

void RoomPage::ShowSentMessage() {
    list->append(QString::fromStdString("You: ") + tempContent);
    model->setStringList(*list);
    ui->listView->setModel(model);
}

void RoomPage::ShowNewMessage(const Message& message) {
    list->append(QString::fromStdString(message.author) + tempContent);
    model->setStringList(*list);
    ui->listView->setModel(model);
}

void RoomPage::ShowLastMessages(const std::vector<Message>& messages){
    for (const auto message : messages) {
        std::string messageAuthor = (message.author == userInfo_.login) ? "You" : message.author;
        list->append(QString::fromStdString(messageAuthor + ": " + message.content));
        model->setStringList(*list);
        ui->listView->setModel(model);
    }
}

void RoomPage::OnBackButtonClicked()
{
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

QStringList RoomPage::getWordList(const QString& path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    //if(file.isOpen())
    QTextStream in(&file);
    QStringList fields;

    while(!in.atEnd()) {
        QString line = in.readLine();
        // qDebug() << line << "\n";
        fields.append(line.split(","));
    }

    // qDebug() << fields;

    return fields;
}

// void RoomPage::ShowOldMessages(const std::vector<Message>& messages){}
// void RoomPage::ShowRoomInfo(const RoomInfo& roomInfo){}
