#pragma once

class HttpListener
{
public:
    virtual void listen() = 0;

    virtual void close() = 0;
};