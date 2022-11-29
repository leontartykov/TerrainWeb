#include "form_http_response.hpp"
#include "server/server_codes.h"

drogon::HttpResponsePtr form_http_response(int &response_code, Json::Value &jsonBody)
{
    drogon::HttpResponsePtr resp;

    if (response_code == SERV_BAD_REQUEST){
        jsonBody["status"] = "error";
        jsonBody["message"] = "BadRequest";
        resp = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        resp.get()->setStatusCode(drogon::HttpStatusCode::k400BadRequest);
    }
    else if (response_code == SERV_NOT_FOUND || response_code == -2 || response_code == -1){
        jsonBody["status"] = "error";
        jsonBody["message"] = "not found";
        resp = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        resp.get()->setStatusCode(drogon::HttpStatusCode::k404NotFound);
    }
    else if (response_code == SERV_FORBIDDEN)
    {
        jsonBody["status"] = "error";
        jsonBody["message"] = "Forbidden";
        resp = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        resp.get()->setStatusCode(drogon::HttpStatusCode::k403Forbidden);
    }
    else if (response_code == SERV_SUCCESS || response_code == 0 || response_code == true){
        resp = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        resp.get()->setStatusCode(drogon::HttpStatusCode::k200OK);
    }
    else if (response_code == SERV_SUCCESS_CREATED){
        resp = drogon::HttpResponse::newHttpJsonResponse(jsonBody);
        resp.get()->setStatusCode(drogon::HttpStatusCode::k201Created);
    }

    return resp;
}

drogon::HttpResponsePtr form_http_response(int &response_code, std::string &filename)
{
    drogon::HttpResponsePtr resp;
    resp = drogon::HttpResponse::newFileResponse(filename);
    resp.get()->setStatusCode(drogon::HttpStatusCode::k200OK);
    resp->addHeader("Server", "Terrain Server");

    return resp;
}
