#pragma once 
#include <QWidget>
#include <QListWidgetItem>
#include "IMainPage.hpp"
#include "IRoomUseCase.hpp"
#include "IWidgetController.hpp"

namespace Ui {
class MainPage;
}

class MainPage : public QWidget,
                 public IMainPage
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

    void ShowRooms(const std::vector<RoomInfo>& rooms) override;
    void ShowError(const std::string& error) override;

    void SetController(IWidgetController* controller) {
        controller_ = controller;
    }

    void SetUseCase(IRoomUseCaseSPtr useCase) {
        useCase_ = useCase;
    }

    // void SetUserInfo(const UserInfo& userInfo) override;

    
public slots:
    void OnCreateRoom();
    void OnRefreshMainPage();
    void OnSelectRoom(QListWidgetItem *item);
    
private:
    Ui::MainPage *ui;

    IRoomUseCaseSPtr useCase_;
    IWidgetController* controller_;
};

