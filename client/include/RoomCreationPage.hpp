#pragma once
#include "IRoomCreationPage.hpp"

#include <QWidget>
#include <QListWidget>
#include <string>
#include <vector>
#include <optional>
#include "IWidgetController.hpp"
#include "IRoomUseCase.hpp"

namespace Ui {
class RoomCreationPage;
}

class RoomCreationPage : public QWidget,
                         public IRoomCreationPage
{
    Q_OBJECT

public:
    explicit RoomCreationPage(QWidget *parent = nullptr);
    ~RoomCreationPage();

    void ShowError(const std::string& error) override;

    void SetUseCase(IRoomUseCaseSPtr roomUseCase) {
        roomUseCase_ = roomUseCase;
    }

    void SetController(IWidgetController* controller) {
        controller_ = controller;
    }

private slots:
    void OnCreateRoomButtonClicked();
    void OnBackButtonClicked();
    void OnAddUserButtonClicked();

private:
    Ui::RoomCreationPage *ui;
    std::vector<std::string> members;
    IWidgetController* controller_;
    IRoomUseCaseSPtr roomUseCase_;
    void ClearForm();
};
