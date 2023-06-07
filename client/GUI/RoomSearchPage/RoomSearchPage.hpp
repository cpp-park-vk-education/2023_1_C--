#pragma once
#include <QWidget>
#include <QListWidget>
#include "IWidgetController.hpp"
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
    
    void SetUseCase(IRoomUseCaseSPtr roomUseCase) {
        roomUseCase_ = roomUseCase;
    }

    void SetController(IWidgetController* controller) {
        controller_ = controller;
    }

private slots:
    void OnSelectRoom(QListWidgetItem *item);
    void OnSearchButtonClicked();
    void OnBackButtonClicked();


private:
    Ui::RoomSearchPage *ui;
    IWidgetController* controller_;
    IRoomUseCaseSPtr roomUseCase_;
};
