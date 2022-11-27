#include <drogon/drogon.h>

int main() {
    //Set HTTP listener address and port
    drogon::app().addListener("127.0.0.1", 7000);
    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop

    drogon::app().registerPostHandlingAdvice(
            [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
            resp->addHeader("Server", "Terrain Server");
            resp->addHeader("Access-Control-Allow-Methods", "OPTIONS,POST,GET, Post, Get, Delete, Put, Patch");
            resp->addHeader("Access-Control-Allow-Origin", "*");
            resp->addHeader("Access-Control-Allow-Headers", "Accept, Authorization, Cache-Control, \
                            Content-Type, DNT, UUID, If-Modified-Since, Keep-Alive, Origin, User-Agent, X-Requested-With");
            });
    drogon::app().run();
    return 0;
}
