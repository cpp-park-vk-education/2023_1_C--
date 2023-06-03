#pragma once
#include <QWidget>
#include <QStringListModel>
#include <QCompleter>
#include "IRoomUseCase.hpp"
#include "IRoomPage.hpp"

namespace Ui {
class RoomPage;
}

class RoomPage : public QWidget, 
                 public IRoomPage {
    Q_OBJECT
public:
    explicit RoomPage(QWidget *parent = nullptr);
    ~RoomPage();

    void ShowSentMessage() override;
    void ShowAddedUser(const UserInfo& info) override;
    void ShowRoomInfo(const RoomInfo& roomInfo) override;
    void ShowLastMessages(const std::vector<Message>& messages) override;
    void ShowNewMessage(const Message& message) override;
    void ShowError(const std::string& error) override;

    void SetUseCase(IRoomUseCaseSPtr useCase) {
        useCase_ = useCase;
    }

    void SetUserInfo(const UserInfo& userInfo) override {
        userInfo_ = userInfo;
    }

    void SetMessageCompleter(QCompleter* messageCompleter);
    void SetUserCompleter(QCompleter* userCompleter);

private slots:
    void OnBackButtonClicked();
    void OnSendButtonClicked();
    void OnAddUserButtonClicked();

private:
    QString tempContent;
    QString tempNickname;

    UserInfo userInfo_;
    RoomInfo roomInfo_;

    QMap<QString, QString> members;

    Ui::RoomPage *ui;
    IRoomUseCaseSPtr useCase_;
    
    QStringListModel *messagesListModel;
    QStringList *messagesList;

    QStringListModel *membersListModel;
    QStringList *membersList;
};