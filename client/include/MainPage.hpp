#pragma once 
#include <QWidget>
#include <QListWidget>
#include <optional>
#include "IMainPageUi.hpp"
#include "IRoomSwitcher.hpp"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget,
                 public IMainPageUi
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

    void ShowMainPage(std::vector<RoomData> rooms) override;

    void ShowRoomSearchPage() override {
        roomSwitcher_->ShowRoomSearchPage();
    }

    void ShowRoomCreationPage() {
        roomSwitcher_->ShowRoomCreationPage();
    }

    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

    std::optional<RoomData> FindRoom(const int roomId);
    
public slots:
    void CreateRoom() {
        ShowRoomCreationPage();
    }

    void SearchRoom() {
        ShowRoomSearchPage();
    }

    void SelectRoom(QListWidgetItem *item);
    
private:
    Ui::MainPage *ui;
    std::vector<RoomData> rooms_;
    IRoomSwitcherSPtr roomSwitcher_;
};
