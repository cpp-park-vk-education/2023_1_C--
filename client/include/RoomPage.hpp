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
    void ShowAddedUser(const UserInfo& info) override;
    void ShowRoomInfo(const RoomInfo& roomInfo) override;
    // void ShowRoomName(const std::string& name) override;
    void ShowLastMessages(const std::vector<Message>& messages) override;
    // void ShowOldMessages(const std::vector<Message>& messages) override;
    void ShowNewMessage(const Message& message) override;

    void SetUseCase(IRoomUseCaseSPtr useCase) {
        useCase_ = useCase;
    }

    void SetController(IWidgetController* controller) {
        controller_ = controller;
    }

    void SetUserInfo(const UserInfo& userInfo) override {
        userInfo_ = userInfo;
    }

private slots:
    void OnBackButtonClicked();
    void OnSendButtonClicked();
    void OnAddUserButtonClicked();
    void OnGetNewMessage();

private:
    QString tempContent;
    QString tempNickname;

    UserInfo userInfo_; //
    RoomInfo roomInfo_; 

    Ui::RoomPage *ui;
    IRoomUseCaseSPtr useCase_;
    IWidgetController* controller_;

    QTimer* timer_;
    QStringListModel *messagesListModel;
    QStringList *messagesList;
    QStringListModel *membersListModel;
    QStringList *membersList;
    QCompleter *completer;
    QStringList getWordList(const QString& path);
    QString getUserNickname(const std::string& login);
};
