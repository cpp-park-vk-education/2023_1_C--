#pragma once
#include <string>
#include <memory>

class ISignupPage {
public:
    virtual ~ISignupPage() {}
    virtual void ShowError(const std::string& error) = 0;
};

using ISignupPageSPtr = std::shared_ptr<ISignupPage>;
