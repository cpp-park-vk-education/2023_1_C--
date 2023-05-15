#include "RoomPage.hpp"
#include "ui_RoomPage.h"

RoomPage::RoomPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::RoomPage)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    list = new QStringList();
    completer = new QCompleter(
        getWordList("/home/anastasia/VKedu/Cpp/wordlist.txt"), this);

    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->messageLineEdit->setCompleter(completer);

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->messageLineEdit, SIGNAL(returnPressed()), ui->sendBtn, SIGNAL(clicked()));
}

RoomPage::~RoomPage()
{
    delete ui;
    delete list;
}

void RoomPage::ShowRoomInfo(const RoomInfo& roomInfo){}

void RoomPage::ShowRoomName(const std::string& name){
    ui->roomNameLabel->setText(QString::fromStdString(name));
}

void RoomPage::ShowLastMessages(const std::vector<Message>& messages){}
void RoomPage::ShowOldMessages(const std::vector<Message>& messages){}

void RoomPage::on_backBtn_clicked()
{
    //close thread

}


void RoomPage::on_sendBtn_clicked()
{
    auto content = ui->messageLineEdit->text();
    *list << QString::fromStdString("You: ") + content;
    model->setStringList(*list);
    ui->listView->setModel(model);
    //отправить сообщение
    ui->messageLineEdit->setText("");
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

    qDebug() << fields;

    return fields;
}

