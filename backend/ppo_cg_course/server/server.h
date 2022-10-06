#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/asio.hpp>

#include "async_con.h"

using namespace boost::asio;
using ip::tcp;

class HTTPServerTCP
{
    private:
        boost::asio::io_service& __io_service;
        tcp::acceptor __acceptor;
        void __start_accept();

    public:
        HTTPServerTCP(boost::asio::io_service &io_service);

        std::string read(tcp::socket &socket);
        void send(tcp::socket &socket, const std::string &message);

        void handle_accept(tcp_connection::pointer connection, const boost::system::error_code &error);
};

#endif
