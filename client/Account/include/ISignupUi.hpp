#pragma once
#include <string>
#include <memory>

class ISignupUi {
public:
    virtual ~ISignupUi() {}
    virtual void ShowSignupError(const std::string& error) = 0;
};

using ISignupUiSPtr = std::shared_ptr<ISignupUi>;
