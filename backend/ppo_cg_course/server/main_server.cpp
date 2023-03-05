#include <iostream>

#include "server/http_server/http_server.h"

#include <nghttp2/asio_http2_server.h>
using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;

int main(int argc, char *argv[])
{
    boost::asio::io_service io_service;
    HTTPServerTCP http_server(io_service);
    io_service.run();

    /*boost::system::error_code ec;
      http2 server;

      std::cerr << "handle\n";
      server.handle("/", [](const server::request &req, const server::response &res)
      {
        res.write_head(200);
        res.end("hello, world\n");
      });

      if (server.listen_and_serve(ec, "localhost", "3000")) {
        std::cerr << "error: " << ec.message() << std::endl;
      }

    return 0;*/
}



