#pragma once
#include <string>
#include <memory>

class ILoginPage {
public:
    virtual ~ILoginPage() {}
    virtual void ShowError(const std::string& error) = 0;
};

using ILoginPageSPtr = std::shared_ptr<ILoginPage>;
