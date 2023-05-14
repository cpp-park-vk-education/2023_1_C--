#pragma once
#include <QObject>
#include <QNetworkAccessManager>
#include "ICommunication.hpp"

class NetworkManager: public QObject {

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();
    void Post(QNetworkRequest request, QByteArray data, Callback callback);
    void Get(QNetworkRequest request, Callback callback);

public slots:
    void ResponseHanler(QNetworkReply* reply);

private:
    Callback callback_;
    QNetworkAccessManager manager;
};

