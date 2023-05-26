#include "Communication.hpp"

const std::string ROOT_URL = "http://127.0.0.1:1488/"; // cringe

Request createRequest(const std::string& url, Headers headers) {
    Request request;
    request.SetUrl(ROOT_URL + url);
    for (auto it = headers.begin(); it != headers.end(); ++it)
        request.SetHeader(it->first, it->second);
    return request;
}
