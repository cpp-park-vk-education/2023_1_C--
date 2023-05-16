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
    void ShowRoomSearchPage() override;
    void ShowRoomCreationPage() override;

    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }

    
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
    std::optional<RoomData> FindRoom(const int roomId);
};

