#include "server.h"

HTTPServerTCP::HTTPServerTCP(boost::asio::io_service &io_service) : __io_service(io_service),
    __acceptor(__io_service, tcp::endpoint(tcp::v4(), 8080)){
    __start_accept();
}

void HTTPServerTCP::__start_accept()
{
    tcp_connection::pointer connection = tcp_connection::create(__io_service);
    __acceptor.async_accept(connection->socket(),
            boost::bind(&HTTPServerTCP::handle_accept, this, connection,
            boost::asio::placeholders::error));
}

std::string HTTPServerTCP::read(tcp::socket &socket)
{
    streambuf buffer;
    read_until(socket, buffer, "\n" );

    std::string data = buffer_cast<const char *>(buffer.data());

    return data;
}

void HTTPServerTCP::send(tcp::socket &socket, const std::string &message)
{
    const std::string msg = message + "\n";
    write(socket, buffer(message));
}

void HTTPServerTCP::handle_accept(tcp_connection::pointer connection, const boost::system::error_code &error)
{
    if (!error){
        connection->start();
    }

    __start_accept();
}
