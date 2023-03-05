#include "http_server.h"

HTTPServerTCP::HTTPServerTCP(boost::asio::io_service &io_service) : __io_service(io_service),
    __acceptor(__io_service, tcp::endpoint(tcp::v4(), PORT_NUM)){
    __start_accept();
}

void HTTPServerTCP::__start_accept()
{
    tcp_connection::pointer connection = tcp_connection::create(__io_service);
    std::cout << "port: " << PORT_NUM << "\n";
    __acceptor.async_accept(connection->socket(),
            boost::bind(&HTTPServerTCP::handle_accept, this, connection,
            boost::asio::placeholders::error));
}

void HTTPServerTCP::handle_accept(tcp_connection::pointer connection, const boost::system::error_code &error)
{
    if (!error){
        connection->start();
    }

    __start_accept();
}

