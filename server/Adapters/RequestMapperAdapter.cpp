#include "RequestMapperAdapter.hpp"

void RequestMapperAdapter::service(HttpRequest& request, HttpResponse& response)
{
    auto req = HttpRequestAdapter(&request);

    auto res = HttpResponseAdapter(&response);

    requestMapper->service(&req, &res);
}