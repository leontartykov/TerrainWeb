#include <iostream>

#include "http_server/controllers/http_controllers.hpp"
#include "http_server/controllers/form_http_response.hpp"
#include "error_codes.h"
#include "core/data_access/db_model/postgres/postgres.hpp"


void api::v1::UsersController::set_dbModel(std::shared_ptr<DbModel> dbModel){
    __users_service->set_dbModel(dbModel);
}

/*void api::v1::UsersController::init(std::shared_ptr<DbModel> dbModel)
{
    std::cerr << "init\n";
    __users_service = std::make_shared<UsersService>();
    //set_dbModel(dbModel);
}*/

api::v1::UsersController::UsersController()
{
    __users_service = std::make_shared<UsersService>();
    config_t config = __config.read_config_postgres();

    __users_service->set_dbModel(create_db_model(config));
}

std::shared_ptr<DbModel> api::v1::create_db_model(config_t &config)
{
    std::shared_ptr<DbModel> db_model;
    std::string rdbms = config.dbms_type;

    if (rdbms == "postgresql"){
        std::shared_ptr<Postgres> postgres = std::make_shared<Postgres>();
        db_model = postgres;
    }

    return db_model;
}

api::v1::UsersController::~UsersController(){
    std::cerr << "UserControllerDestructor\n";
}

void api::v1::UsersController::get_info(const HttpRequestPtr &req,
                                        std::function<void (const HttpResponsePtr &)> &&callback,
                                        std::string userId)
{
    int user_id, ret_code, uuid;
    servUsers_t user;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    UserSessions usrSessions;

    try {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = usrSessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            user_id = std::stoi(userId);
            ret_code = __users_service->get(user_id, user);
            jsonBody = form_json_response(user);
            resp = form_http_response(ret_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e){
        std::cerr << e.what();
        ret_code = BAD_REQUEST;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::UsersController::add_new(const HttpRequestPtr &req,
                                       std::function<void (const HttpResponsePtr &)> &&callback)
{
    servUsers_t user;
    int ret_code, uuid;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::shared_ptr<Json::Value> json;
    Json::Value jsonBody;
    UserSessions usrSessions;

    try
    {

        /*token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = usrSessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else
        {*/
            json = req.get()->getJsonObject();

            user.login = (*json)["login"].asString();
            std::cerr << "login: " << user.login << "\n";
            user.password = (*json)["password"].asString();
            user.perm_level = (*json)["perm_level"].asInt();

            ret_code = __users_service->add(user);
            std::cerr << "ret_code: " << ret_code << "\n";
            resp = form_http_response(ret_code, jsonBody);
        //}
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;
        std::cerr << "ret_code: " << ret_code << "\n";
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::UsersController::delete_usr(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,
                                std::string userId)
{
    int user_id, ret_code, uuid;
    std::string token;
    drogon::HttpResponsePtr resp;
    Json::Value jsonBody;
    UserSessions usrSessions;

    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = usrSessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else
        {
            user_id = std::stoi(userId);
            ret_code = __users_service->delete_user(user_id);
            resp = form_http_response(ret_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::UsersController::change_usr_login(const HttpRequestPtr &req,
          std::function<void (const HttpResponsePtr &)> &&callback, std::string userId)
{
    std::string new_login, token;
    json j_complete;
    servUsers_t user;
    int uuid, ret_code;
    drogon::HttpResponsePtr resp;
    Json::Value jsonBody;
    UserSessions usrSessions;

    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = usrSessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else
        {
            j_complete = json::parse(req->bodyData());
            new_login = j_complete["login"];
            user.id = std::stoi(userId);
            user.login = new_login;

            ret_code = __users_service->update(user.id, user);
            resp = form_http_response(ret_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::UsersController::login(
        const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    int ret_code, uuid;
    std::shared_ptr<Json::Value> json;
    servUsers_t user;
    Json::Value jsonBody;
    drogon::HttpResponsePtr resp;
    std::string access_token;

    try
    {
        json = req.get()->getJsonObject();
        user.login = (*json)["login"].asString();
        user.password = (*json)["password"].asString();
        ret_code = __users_service->validate((const servUsers_t)user, uuid);
        std::cerr << "ret_code: " << ret_code << "\n";
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else
        {
            ret_code = __users_service->login(access_token, uuid);
            jsonBody = form_json_response(access_token, uuid);
            std::cerr << "access_token: " << access_token << "\n";
            resp = form_http_response(ret_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}


