#pragma once
#include <string>
#include <memory>

class ILoginUi {
public:
    virtual ~ILoginUi() {}
    virtual void ShowLoginError(const std::string& error) = 0;
};

using ILoginUiSPtr = std::shared_ptr<ILoginUi>;

