#pragma once
#include <QObject>
#include <QSettings>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include "INetworkManager.hpp"

class NetworkManager: public QObject,
                      public INetworkManager {

public:
    NetworkManager(QObject *parent = nullptr);
    void Post(IRequestUPtr request, Callback callback) override;
    void Get(IRequestUPtr request, Callback callback) override;
    
private slots:
    void ResponseHanler(QNetworkReply* reply);

private:
    Callback callback_;
    QNetworkAccessManager* networkManager;
    QNetworkRequest createQNetworkRequest(IRequestUPtr request);
};
