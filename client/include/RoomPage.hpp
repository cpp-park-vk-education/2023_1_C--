#pragma once
#include <QWidget>
#include <QStringListModel>
#include <QCompleter>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include "IRoomPageUi.hpp"
#include "IRoomUseCase.hpp"
#include "IRoomSwitcher.hpp"
#include "RoomData.hpp"

namespace Ui {
class RoomPage;
}

class RoomPage : public QWidget, public IRoomPageUi
{
    Q_OBJECT

public:
    explicit RoomPage(QWidget *parent = nullptr);
    ~RoomPage();

    void SetRoomUseCase(IRoomUseCaseSPtr useCase) {
        useCase_ = std::move(useCase);
    }

    void SetRoomSwitcher(IRoomSwitcherSPtr switcher) {
        switcher_ = std::move(switcher);
    }

    void ShowSentMessage();
    void ShowRoomInfo(const RoomInfo& roomInfo);
    void ShowRoomName(const std::string& name);
    void ShowLastMessages(const std::vector<Message>& messages);
    void ShowOldMessages(const std::vector<Message>& messages);

private slots:
    void on_backBtn_clicked();
    void on_sendBtn_clicked();

private:

    QStringList getWordList(const QString& path);
    QString tempContent;
    RoomInfo roomInfo;
    UserInfo userInfo;
    Ui::RoomPage *ui;
    IRoomUseCaseSPtr useCase_;
    IRoomSwitcherSPtr switcher_;
    QStringListModel *model;
    QStringList *list;
    QCompleter *completer;
};
