#include <QApplication>
#include "AppController.hpp"
#include "MainWindow.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    AppController controller;
    
    controller.mainWindow->setGeometry(0, 0, 800, 480);
    controller.mainWindow->show();
    controller.mainWindow->ShowLoginPage();

    return app.exec();
}
