#ifndef ROOMCREATIONPAGE_HPP
#define ROOMCREATIONPAGE_HPP

#include <QWidget>
#include <QListWidget>
#include <string>
#include <vector>
#include <optional>
#include "IRoomSwitcher.hpp"
#include "IRoomUseCase.hpp"

namespace Ui {
class RoomCreationPage;
}

class RoomCreationPage : public QWidget
{
    Q_OBJECT

public:
    explicit RoomCreationPage(QWidget *parent = nullptr);
    ~RoomCreationPage();

    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

    void SetRoomUseCase(IRoomUseCaseSPtr roomUseCase) {
        roomUseCase_ = roomUseCase;
    }

private slots:
    void OnCreateRoomButton();
    void OnBackButton();
    void OnAddUserButton();

private:
    Ui::RoomCreationPage *ui;
    std::vector<std::string> members;
    
    IRoomSwitcherSPtr roomSwitcher_;
    IRoomUseCaseSPtr roomUseCase_;
};

#endif // ROOMCREATIONPAGE_HPP
