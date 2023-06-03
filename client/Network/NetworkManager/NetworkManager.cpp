#include <vector>
#include <QDebug>
#include <QByteArray>
#include "NetworkManager.hpp"
#include "Response.hpp"

NetworkManager::NetworkManager(QObject *parent) 
    : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &NetworkManager::ResponseHanler);
}

QNetworkRequest NetworkManager::createQNetworkRequest(IRequestUPtr request) {
    auto qRequest = QNetworkRequest(QUrl(QString::fromStdString(request->GetUrl())));

    auto headers = request->GetHeaders();
    for (auto it = headers.begin(); it != headers.end(); ++it)
        qRequest.setRawHeader(QByteArray(it->first.c_str(), it->first.size()),
                              QByteArray(it->second.c_str(), it->second.size()));
    qDebug() << qRequest.url().toString();
    for (const auto& rawHeader : qRequest.rawHeaderList())
        qDebug() << rawHeader << ":" << qRequest.rawHeader(rawHeader);
    return qRequest;
}

void NetworkManager::Post(IRequestUPtr request, Callback callback) {
    callback_ = callback;
    auto data = QByteArray(request->GetBody().data(), request->GetBody().size());
    networkManager->post(createQNetworkRequest(std::move(request)), data);
    qDebug() << data;
}

void NetworkManager::Get(IRequestUPtr request, Callback callback) {
    callback_ = callback;
    networkManager->get(createQNetworkRequest(std::move(request)));
}

void NetworkManager::ResponseHanler(QNetworkReply* reply) {
    qDebug() << reply->error() << '\n';
    if (!reply->error()) {
        auto body = reply->readAll();
        Response response(true, std::vector<char>(body.begin(), body.end()));
        callback_(std::make_unique<Response>(response));
    } else {
        Response response(false, reply->errorString().toStdString());
        callback_(std::make_unique<Response>(response));
    }
}
