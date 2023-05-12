#pragma once
#include <string>
#include <memory>

class IAccountUi {
public:
    virtual ~IAccountUi() {}
    virtual void ShowError(const std::string& error) = 0;
};

using IAccountUiSPtr = std::shared_ptr<IAccountUi>;

