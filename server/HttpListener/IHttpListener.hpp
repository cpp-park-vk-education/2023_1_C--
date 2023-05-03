#pragma once

class IHttpListener
{
public:
    virtual void listen() = 0;

    virtual void close() = 0;
};