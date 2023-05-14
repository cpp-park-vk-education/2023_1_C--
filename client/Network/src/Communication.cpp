#include "Communication.hpp"

const std::string ROOT = "http://127.0.0.1:8000/";

QNetworkRequest CreateRequest(const std::string& url,
                              const std::string& contentType) {
    QNetworkRequest qNetworktRequest;
    qNetworktRequest.setUrl(QUrl(QString::fromStdString(ROOT + url)));
    qNetworktRequest.setRawHeader(QByteArray("Content-Type"),
                                  QByteArray::fromStdString(contentType));
    return qNetworktRequest;
}
