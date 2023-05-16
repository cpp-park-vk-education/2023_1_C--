#include "RoomPage.hpp"
#include "ui_RoomPage.h"
#include "mclineedit.h"

RoomPage::RoomPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::RoomPage)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    list = new QStringList();
    auto timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(on_get_new_msg()));
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

void RoomPage::on_get_new_msg()
{
    useCase_->GetNewMessage(33);
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
    tempContent = ui->messageLineEdit->text();
    Message message;
    message.roomID = roomData_.info.id;
    message.content = tempContent.toStdString();
    message.author = userInfo_.login; 
    useCase_->SendMessage(message);

    *list << QString::fromStdString("You: ") + tempContent;
    model->setStringList(*list);
    ui->listView->setModel(model);
    ui->messageLineEdit->setText("");
}

void RoomPage::ShowSentMessage() {
    *list << QString::fromStdString("You: ") + tempContent;
    model->setStringList(*list);
    ui->listView->setModel(model);
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
        qDebug() << line << "\n";
        fields.append(line.split(","));
    }

    qDebug() << fields;

    return fields;
}

void RoomPage::SetRoomUseCase(IRoomUseCaseSPtr useCase) {
    useCase_ = std::move(useCase);
}

void RoomPage::SetRoomSwitcher(IRoomSwitcherSPtr switcher) {
    switcher_ = std::move(switcher);
}

void RoomPage::SetRoomData(const RoomData& roomData) {
    roomData_ = roomData; 
}

void RoomPage::SetUserInfo(const UserInfo& userInfo) {
    userInfo_ = userInfo;
}
