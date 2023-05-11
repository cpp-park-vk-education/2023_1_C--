#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("Teamgram Server");

    qWarning("Application has started");

    app.exec();
}