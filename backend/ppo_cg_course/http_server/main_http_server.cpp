#include "http_server/http_server_10/http_server_10.hpp"

int main() {
    //drogon::app().addListener("127.0.0.1", 7000);

    HttpServer10 server;
    server.run_server();

    return 0;
}
