#pragma once 
#include <QWidget>
#include <QListWidget>
#include "IMainPageUi.hpp"
#include "IRoomSwitcher.hpp"
#include <optional>

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

    std::optional<RoomData> FindRoom(const int roomId);

    void SetRoomSwitcher(IRoomSwitcherSPtr roomSwitcher) {
        roomSwitcher_ = roomSwitcher;
    }
    
public slots:
    void SelectRoom(QListWidgetItem *item);
    void OnSelectButtonClicked();
    
private:
    Ui::MainPage *ui;
    std::vector<RoomData> rooms_;
    IRoomSwitcherSPtr roomSwitcher_;
};

