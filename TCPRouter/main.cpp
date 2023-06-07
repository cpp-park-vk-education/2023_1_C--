#include <QCoreApplication>

#include "TCPMessageRouter.hpp"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("Teamgram TcpRouter");

    auto settings = new QSettings("../../TCPRouter/config.ini", QSettings::IniFormat, &app);

    settings->beginGroup("router");
    
    auto router = new TcpMessageRouter(&app);

    return app.exec();
}