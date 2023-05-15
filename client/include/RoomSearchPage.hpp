#pragma once
#include <QWidget>
#include <QListWidget>
#include <optional>
#include "IRoomSwitcher.hpp"
#include "IRoomUseCase.hpp"

namespace Ui {
class RoomSearchPage;
}

class RoomSearchPage : public QWidget
{
    Q_OBJECT

public:
    explicit RoomSearchPage(QWidget *parent = nullptr);
    ~RoomSearchPage();
    
    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

    void SetRoomUseCase(IRoomUseCaseSPtr roomUseCase) {
        roomUseCase_ = roomUseCase;
    }


public slots:
    void SelectRoom(QListWidgetItem *item);
    void SearchRoom();
    void Back();


private:
    Ui::RoomSearchPage *ui;
    IRoomSwitcherSPtr roomSwitcher_;
    IRoomUseCaseSPtr roomUseCase_;
    std::vector<RoomData> rooms_;
};
