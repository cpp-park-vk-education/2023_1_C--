#pragma once
#include <QWidget>
#include "LoginPage.hpp"
#include "MainPage.hpp"
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

    void SetLoginPage(LoginPage* loginPage);
    void SetMainPage(MainPage* loginPage);

    void ShowLoginPage() override;
    // void ShowSignupPage() override;
    // void ShowUserSettingPage() override;
    void ShowRoomPage() override;
    void ShowMainPage() override;
    void ShowRoomInfo() override;

private:
    Ui::MainWindow *ui;
    LoginPage* loginPage_;
    MainPage* mainPage_;
};
