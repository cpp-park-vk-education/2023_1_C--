#pragma once
#include <QWidget>
#include "LoginPage.hpp"
#include "SignupPage.hpp"
#include "MainPage.hpp"
#include "RoomPage.hpp"
#include "RoomSearchPage.hpp"
#include "RoomCreationPage.hpp"
#include "IWidgetController.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QWidget, 
                   public IWidgetController
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetLoginPage(LoginPage* page);
    void SetSignupPage(SignupPage* page);
    void SetMainPage(MainPage* page);
    void SetRoomPage(RoomPage* page);
    void SetRoomSearchPage(RoomSearchPage* page);
    void SetRoomCreationPage(RoomCreationPage* page);

    void ShowLoginPage() override;
    void ShowSignupPage() override;
    // void ShowUserSettingPage() override;
    void ShowRoomPage() override;
    void ShowMainPage() override;
    // void ShowRoomInfo() override;
    void ShowRoomSearchPage() override;
    void ShowRoomCreationPage() override;


private:
    Ui::MainWindow *ui;
    int loginPageIndex;
    int signupPageIndex;
    int mainPageIndex;
    int roomPageIndex;
    int roomSearchPageIndex;
    int roomCreationPageIndex;
};
