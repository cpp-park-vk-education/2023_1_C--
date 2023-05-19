#include <vector>
#include <QDebug>
#include <QNetworkReply>
#include <QByteArray>
#include "NetworkManager.hpp"
#include "Communication.hpp"

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, 
            this, &NetworkManager::ResponseHanler);
}

NetworkManager::~NetworkManager() {}

void NetworkManager::Post(QNetworkRequest request, QByteArray data, Callback callback) {
    QNetworkReply* reply = networkManager->post(request, data);
    callback_ = callback;
    qDebug() << "Post request was sent";
}

void NetworkManager::Get(QNetworkRequest request, Callback callback) {
    QNetworkReply* reply = networkManager->get(request);
    callback_ = callback;
    qDebug() << "Get request was sent";
}

void NetworkManager::ResponseHanler(QNetworkReply* reply) {
    auto status = reply->error();
    if (status == QNetworkReply::NoError) {
        qDebug() << "Status: 200";
        QByteArray body = reply->readAll();
        Response response(200, std::vector<char>(body.begin(), body.end()));
        callback_(std::make_unique<Response>(response));
    } else {
        Response response(static_cast<const int>(status), std::vector<char>());
        qDebug() << "Status: " << response.GetStatus();
        callback_(std::make_unique<Response>(response));
    }
}
