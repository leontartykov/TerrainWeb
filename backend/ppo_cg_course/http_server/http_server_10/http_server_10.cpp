#include "http_server_10.hpp"
#include "http_server/controllers/http_controllers.hpp"

HttpServer10::HttpServer10()
{
    drogon::app().loadConfigFile("../ppo_cg_course/http_server/config.json");

    drogon::app().registerPostHandlingAdvice(
            [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
            resp->addHeader("Server", "Terrain Server");
            resp->addHeader("Access-Control-Allow-Methods", "Options, Post, Get, Delete, Put, Patch");
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Headers", "Accept, Authorization, Cache-Control, \
                            Content-Type, DNT, UUID, If-Modified-Since, Keep-Alive, Origin, User-Agent, X-Requested-With");
            resp->addHeader("Server", "Terrain Server");
            });
    //__usersController = std::make_shared<api::v1::UsersController>();
    //config_t config = __config.read_config_postgres();
    //__dbModel = __create_db_model(config);

    //__usersController->set_dbModel(__dbModel);
    //__terrainsController.set_dbModel(__dbModel);
    //drogon::internal::getControllerObj<api::v1::UsersController>().init("hello world");
}

void HttpServer10::run_server(){
    drogon::app().run();
}
