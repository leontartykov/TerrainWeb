#ifndef _FORM_HTTP_RESPONSE_HPP_
#define _FORM_HTTP_RESPONSE_HPP_

#include <drogon/HttpController.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <drogon/HttpAppFramework.h>
#include "http_server/json_former/json_former.hpp"

drogon::HttpResponsePtr form_http_response(int &response_code, Json::Value &json);
drogon::HttpResponsePtr form_http_response(int &response_code, std::string &filename);

#endif
