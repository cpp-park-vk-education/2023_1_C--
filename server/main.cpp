#include <QCoreApplication>
#include <QtWebApp/httpserver/httplistener.h>

#include "HttpRequestMapper.hpp"
#include "LoginController.hpp"
#include "RequestMapperAdapter.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    app.setApplicationName("Teamgram Server");

    auto settings = new QSettings("../../server/config.ini", QSettings::IniFormat, &app);

    settings->beginGroup("listener");

    std::map<std::string, std::unique_ptr<IHttpRequestHandler>> map;

    map.insert(
        std::make_pair("/login", std::make_unique<LoginController>())
    );

    new HttpListener(
        settings, 
        new RequestMapperAdapter(
            std::make_unique<HttpRequestMapper>(std::move(map)), &app
        ),
        &app);

    app.exec();
}