#pragma once
#include <string>

class IRoomCreationPage {
public:
    virtual ~IRoomCreationPage() {}
    virtual void ShowError(const std::string& error) = 0;
};
