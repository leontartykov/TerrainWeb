#include <iostream>

#include "http_server/controllers/http_controllers.hpp"
#include "http_server/controllers/form_http_response.hpp"
#include "server/server_codes.h"

void api::v1::UsersController::get_info(const HttpRequestPtr &req,
                                        std::function<void (const HttpResponsePtr &)> &&callback,
                                        std::string userId)
{
    int user_id, response_code, uuid;
    dbUsers_t user;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else{
            user_id = std::stoi(userId);
            response_code = __users_service.get(user_id, user);
            jsonBody = form_json_response(user);
            resp = form_http_response(response_code, jsonBody);
            callback(resp);
        }
    }
    catch (std::exception &e){
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
}

void api::v1::UsersController::add_new(const HttpRequestPtr &req,
                                       std::function<void (const HttpResponsePtr &)> &&callback)
{
    dbUsers_t user;
    int response_code, uuid;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::shared_ptr<Json::Value> json;
    Json::Value jsonBody;

    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else
        {
            json = req.get()->getJsonObject();

            user.login = (*json)["login"].asString();
            user.password = (*json)["password"].asString();
            user.perm_level = (*json)["perm_level"].asInt();

            response_code = __users_service.add(user);
            resp = form_http_response(response_code, jsonBody);
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }

    callback(resp);
}

void api::v1::UsersController::delete_usr(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,
                                std::string userId)
{
    int user_id, response_code, uuid;
    dbUsers_t user;
    std::string token;
    drogon::HttpResponsePtr resp;
    Json::Value jsonBody;

    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else
        {
            user_id = std::stoi(userId);
            response_code = __users_service.delete_user(user_id);
            resp = form_http_response(response_code, jsonBody);
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
    callback(resp);
}

void api::v1::UsersController::change_usr_login(const HttpRequestPtr &req,
          std::function<void (const HttpResponsePtr &)> &&callback, std::string userId)
{
    std::string new_login, token;
    json j_complete;
    dbUsers_t user;
    int uuid, response_code;
    drogon::HttpResponsePtr resp;
    Json::Value jsonBody;

    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else
        {
            j_complete = json::parse(req->bodyData());
            new_login = j_complete["login"];
            user.id = std::stoi(userId);
            user.login = new_login;

            response_code = __users_service.update(user.id, user);
            resp = form_http_response(response_code, jsonBody);
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
    callback(resp);
}

void api::v1::UsersController::log_in_to_system(
        const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    int response_code;
    auto json = req.get()->getJsonObject();
    dbUsers_t user;
    std::string access_token;
    JWTUser jwt_user;
    Json::Value jsonBody;
    drogon::HttpResponsePtr resp;

    try
    {
        user.login = (*json)["login"].asString();
        user.password = (*json)["password"].asString();
        if (!__users_service.validate(user)){
            std::cerr << "Такого пользователя не существует.\n";
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else
        {
            response_code = SERV_SUCCESS;
            access_token = jwt_user.create_token();
            __sessions.add(user.id, access_token);
            jsonBody = form_json_response(access_token, user.id);
            resp = form_http_response(response_code, jsonBody);
        }
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
    callback(resp);
}

bool api::v1::UserSessions::check_usr_authorization(std::string &token, int &uuid)
{
    bool success = true;

    try{
        if (!token.empty()){
            success = this->check_access_token(uuid, token);
        }
        else{
            success = false;
        }
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        success = false;
    }
    return success;
}
