#pragma once 
#include <QWidget>
#include "IMainPageUi.hpp"

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

    void ShowMainPage(const std::vector<RoomData>& rooms) override;
    
private:
    Ui::MainPage *ui;
};

