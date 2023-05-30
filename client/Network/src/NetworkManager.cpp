#include <vector>
#include <QDebug>
#include <QNetworkReply>
#include <QByteArray>
#include "NetworkManager.hpp"
#include "Communication.hpp"

static QNetworkRequest convertToQRequest(IRequestUPtr request) {
    auto qRequest = QNetworkRequest(QUrl(QString::fromStdString(request->GetUrl())));

    auto headers = request->GetHeaders();
    for (auto it = headers.begin(); it != headers.end(); ++it)
        qRequest.setRawHeader(QByteArray(it->first.c_str()), QByteArray(it->second.c_str()));

    return qRequest;
}

NetworkManager::NetworkManager(QObject *parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &NetworkManager::ResponseHanler);
}

void NetworkManager::Post(IRequestUPtr request, Callback callback) {
    callback_ = callback;
    networkManager->post(convertToQRequest(std::move(request)),
                         QByteArray(request->GetBody().data()));
}

void NetworkManager::Get(IRequestUPtr request, Callback callback) {
    callback_ = callback;
    networkManager->get(convertToQRequest(std::move(request)));
}

void NetworkManager::ResponseHanler(QNetworkReply* reply) {
    qDebug() << reply->error();
    if (reply->error() == QNetworkReply::NoError) {
        auto body = reply->readAll();
        Response response(true, std::vector<char>(body.begin(), body.end()));
        callback_(std::make_unique<Response>(response));
    } else {
        Response response(false, reply->errorString().toStdString());
        callback_(std::make_unique<Response>(response));
    }
}
