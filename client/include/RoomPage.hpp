#ifndef ROOMPAGE_HPP
#define ROOMPAGE_HPP

#include <QWidget>
#include "IRoomSwitcher.hpp"

namespace Ui {
class RoomPage;
}

class RoomPage : public QWidget
{
    Q_OBJECT

public:
    explicit RoomPage(QWidget *parent = nullptr);
    ~RoomPage();

    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

private:
    Ui::RoomPage *ui;
    IRoomSwitcherSPtr roomSwitcher_;
};

#endif // ROOMPAGE_HPP
