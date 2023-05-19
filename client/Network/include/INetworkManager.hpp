#pragma once 
#include <QNetworkAccessManager>
#include "ICommunication.hpp"
#include "INetworkManager.hpp"

class INetworkManager {
public:
    virtual ~INetworkManager() {}
    virtual void Post(QNetworkRequest request, QByteArray data, Callback callback) = 0;
    virtual void Get(QNetworkRequest request, Callback callback) = 0;
};

using INetworkManagerSPtr = std::shared_ptr<INetworkManager>;
