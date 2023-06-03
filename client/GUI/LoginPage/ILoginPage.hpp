#pragma once
#include <string>

class ILoginPage {
public:
    virtual ~ILoginPage() {}
    virtual void ShowError(const std::string& error) = 0;
};
