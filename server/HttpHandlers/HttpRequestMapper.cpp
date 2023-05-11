#include "HttpRequestMapper.hpp"

void HttpRequestMapper::service(IHttpRequest* request, IHttpResponse* response)
{
    auto path = request->getPath();

    if (path.empty())
    {
        response->setStatus(401, "error");
        return;
    }

    auto controller = controllerMap.find(path);

    if (controller == controllerMap.end())
    {
        response->setStatus(401, "bad controller");
        return;
    }

    controller->second->service(request, response);
}