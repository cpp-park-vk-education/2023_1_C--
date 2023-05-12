#pragma once
#include "ICommunication.hpp"

class INetworkManager {
public:
    virtual ~INetworkManager() {}
    virtual void Post(IRequestUPtr request, Callback callback) = 0;
    virtual void Get(IRequestUPtr request, Callback callback) = 0;
};

using INetworkManagerSPtr = std::shared_ptr<INetworkManager>;
