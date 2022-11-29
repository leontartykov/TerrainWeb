#ifndef _HTTP_SERVER_H_
#define _HTTP_SERVER_H_

#include <boost/asio.hpp>

#include "./server/async_con.h"

#define PORT_NUM 7004

using namespace boost::asio;
using ip::tcp;

struct request
{
    std::string method;
    std::string uri;
    int http_v_major;
    int http_v_minor;
};

class HTTPServerTCP
{
    private:
        boost::asio::io_service& __io_service;
        tcp::acceptor __acceptor;
        void __start_accept();

    public:
        HTTPServerTCP(boost::asio::io_service &io_service);

        void handle_accept(tcp_connection::pointer connection, const boost::system::error_code &error);
};

#endif
