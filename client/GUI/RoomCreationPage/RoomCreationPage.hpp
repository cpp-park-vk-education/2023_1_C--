#pragma once
#include "IRoomCreationPage.hpp"
#include <QWidget>
#include <QCompleter>
#include <QVector>
#include <QString>
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

    void SetWordCompleter(QCompleter* wordCompleter);
    void SetUserCompleter(QCompleter* userCompleter);

private slots:
    void OnCreateRoomButtonClicked();
    void OnBackButtonClicked();
    void OnAddUserButtonClicked();

private:
    Ui::RoomCreationPage *ui;
    QVector<QString> members;
    IRoomUseCaseSPtr roomUseCase_;
    void clearPage();
};
