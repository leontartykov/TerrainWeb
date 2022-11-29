#include "http_server_10.hpp"

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
}

void HttpServer10::run_server(){
    drogon::app().run();
}
