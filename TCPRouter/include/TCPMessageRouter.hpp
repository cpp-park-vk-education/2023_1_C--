#pragma once

#include <QObject>
#include <QVector>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <memory>
#include <QTcpServer>
#include <QQueue>
#include <QSettings>

class UserConnection
{
public:
    UserConnection() {}
    UserConnection(const QString& login, QTcpSocket* socket)
        : login(login), socket(socket){}
    friend bool operator==(const QString& l, const UserConnection& r);

    friend bool operator!=(const QString& l, const UserConnection& r);

    friend class TcpMessageRouter;

private:
    QString login;

    QTcpSocket* socket;
};

class TcpMessageRouter : public QObject
{
    Q_DISABLE_COPY(TcpMessageRouter)
public:

    explicit TcpMessageRouter(QObject* parent = (QObject*)nullptr) : QObject(parent)
    {
        server = new QTcpServer(this);

        connect(server, &QTcpServer::newConnection, this, &TcpMessageRouter::slotNewConnection);

        if (!server->listen(QHostAddress("0.0.0.0"), 1337))
            qDebug() << "Router error\n";
        else qDebug() << "Router started on port 1337\n";
    }

    TcpMessageRouter& operator=(TcpMessageRouter&& other);

    void sendSignalToUsersFromRoom(const int roomId, const QString& login);

public slots:
    void slotNewConnection();

    void slotServerRead();

    void slotPrimeSocketRead();

private:
    void insert(const int roomId, UserConnection&& userConnection);

    void configurePrimeSocket(QTcpSocket* socket);

    QTcpServer* server;

    QTcpSocket* primeSocket = nullptr;

    QQueue<QTcpSocket*> socketQueue;

    QMap<int, QVector<UserConnection>> connectionMap;
};

