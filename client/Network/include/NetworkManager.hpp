#pragma once
#include <QObject>
#include <QNetworkAccessManager>
#include "INetworkManager.hpp"


class NetworkManager: public QObject,
                      public INetworkManager {

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();
    void Post(QNetworkRequest request, QByteArray data, Callback callback) override;
    void Get(QNetworkRequest request, Callback callback) override;

public slots:
    void ResponseHanler(QNetworkReply* reply);

private:
    Callback callback_;
    QNetworkAccessManager* networkManager;
};

