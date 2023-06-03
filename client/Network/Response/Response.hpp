#pragma once
#include "IResponse.hpp"

class Response : public IResponse {
public:
    Response(bool status, std::vector<char>&& body) 
        : status_(status), body_(body) {}

    Response(bool status, std::string&& description) 
        : status_(status), description_(description) {}

    bool GetStatus() override { return status_; }

    std::string GetDescreption() override { return description_; };
    
    std::vector<char> GetBody() override { return body_; }
    
private:
    bool status_;
    std::string description_;
    std::vector<char> body_;
};
