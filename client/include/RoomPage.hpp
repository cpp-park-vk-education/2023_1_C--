#pragma once

#include <QWidget>
#include "IRoomPageUi.hpp"
#include "IRoomUseCase.hpp"
#include "IRoomSwitcher.hpp"

namespace Ui {
class RoomPage;
}

class RoomPage : public QWidget, public IRoomPageUi
{
    Q_OBJECT

public:
    explicit RoomPage(QWidget *parent = nullptr);
    ~RoomPage();

    void SetUseCase(IRoomUseCaseUPtr useCase) {
        useCase_ = std::move(useCase);
    }

    void ShowRoomInfo(const RoomInfo& roomInfo);
    void ShowRoomName(const std::string& name);
    void ShowLastMessages(const std::vector<Message>& messages);
    void ShowOldMessages(const std::vector<Message>& messages);

private:
    Ui::RoomPage *ui;
    IRoomUseCaseUPtr useCase_;
    IRoomSwitcherSPtr switcher_;
};
