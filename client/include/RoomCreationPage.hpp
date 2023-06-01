#pragma once
#include "IRoomCreationPage.hpp"
#include <QWidget>
#include <QStringListModel>
#include <QCompleter>
#include <QHash>
#include <QString>
#include <QFile>
#include <QTextStream>
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


private slots:
    void OnCreateRoomButtonClicked();
    void OnBackButtonClicked();
    void OnAddUserButtonClicked();

private:
    Ui::RoomCreationPage *ui;
    std::vector<std::string> members;
    IRoomUseCaseSPtr roomUseCase_;
    QCompleter *userCompleter;
    QCompleter *nameCompleter;
    void ClearForm();
    QStringList getWordList(const QString& path);
};
