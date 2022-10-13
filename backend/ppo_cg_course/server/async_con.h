#ifndef _ASYN_CON_H_
#define _ASYN_CON_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/beast/http.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/optional/optional_io.hpp>

#include "../core/data_access/postgres/postgres_init/postgres.h"

using namespace boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using ip::tcp;

class tcp_connection: public boost::enable_shared_from_this<tcp_connection>
{
    private:
        tcp::socket __socket;
        std::string __message;
        http::request<http::string_body> __request;
        streambuf response;
        char __data[1024];

        Postgres __postgres;                            //postgres database

        bool __handle_post_request();
        bool __handle_get_request();
public:
        typedef boost::shared_ptr<tcp_connection> pointer;

        static pointer create(io_service &io_context);
        tcp_connection(io_service &io_context);

        void start();
        void handle_write(const boost::system::error_code &error, size_t bytes_transferred);
        bool handle_read();
        tcp::socket &socket();
};

#endif
