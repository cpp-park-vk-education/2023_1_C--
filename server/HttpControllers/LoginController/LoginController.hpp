#pragma once

#include "IHttpRequestHandler.hpp"
#include "LoginService.hpp"

class LoginController : public IHttpRequestHandler
{
    void service(IHttpRequest*, IHttpResponse*) override;
};