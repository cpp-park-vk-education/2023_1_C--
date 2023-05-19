#pragma once
#include <QWidget>
#include <QStringListModel>
#include <QCompleter>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include "IRoomUseCase.hpp"
#include "IRoomPage.hpp"
#include "IWidgetController.hpp"
#include "RoomData.hpp"

namespace Ui {
class RoomPage;
}

class RoomPage : public QWidget, 
                 public IRoomPage
{
    Q_OBJECT

public:
    explicit RoomPage(QWidget *parent = nullptr);
    ~RoomPage();

    void ShowSentMessage() override;
    // void ShowRoomInfo(const RoomInfo& roomInfo) override;
    void ShowRoomName(const std::string& name) override;
    void ShowLastMessages(const std::vector<Message>& messages) override;
    // void ShowOldMessages(const std::vector<Message>& messages) override;
    void ShowNewMessage(const Message& message) override;

    void SetUseCase(IRoomUseCaseSPtr useCase) {
        useCase_ = useCase;
    }

    void SetController(IWidgetController* controller) {
        controller_ = controller;
    }

    void SetData(const RoomInfo& roomInfo, 
                 const UserInfo& userInfo) override {
        roomInfo_ = roomInfo;
        userInfo_ = userInfo;
    }

private slots:
    void OnBackButtonClicked();
    void OnSendButtonClicked();
    void OnGetNewMessage();

private:
    QString tempContent;

    UserInfo userInfo_;
    RoomInfo roomInfo_;

    Ui::RoomPage *ui;
    IRoomUseCaseSPtr useCase_;
    IWidgetController* controller_;

    QStringListModel *model;
    QStringList *list;
    QCompleter *completer;
    QStringList getWordList(const QString& path);
};
