#include <vector>
#include <QDebug>
#include <QNetworkReply>
#include <QByteArray>
#include "NetworkManager.hpp"
#include "Communication.hpp"

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent) {}

NetworkManager::~NetworkManager() {}

void NetworkManager::Post(QNetworkRequest request, QByteArray data, Callback callback) {
    QNetworkReply* reply = manager.post(request, data);
    // qDebug() << "Post request was sent";
    callback_ = callback;
    connect(&manager, &QNetworkAccessManager::finished,
            this, &NetworkManager::ResponseHanler);
}

void NetworkManager::Get(QNetworkRequest request, Callback callback) {
    QNetworkReply* reply = manager.get(request);
    // qDebug() << "Get request was sent";
    callback_ = callback;
    connect(&manager, &QNetworkAccessManager::finished, 
            this, &NetworkManager::ResponseHanler);
}

void NetworkManager::ResponseHanler(QNetworkReply* reply) {
    auto status = reply->error();
    if (status == QNetworkReply::NoError) {
        QByteArray body = reply->readAll();
        Response response(200, std::vector<char>(body.begin(), body.end()));
        // qDebug() << "Status: 200";
        callback_(std::make_unique<Response>(response));
    } else {
        Response response(static_cast<const int>(status), std::vector<char>());
        // qDebug() << "Status: " << response.GetStatus();
        callback_(std::make_unique<Response>(response));
    }
}
