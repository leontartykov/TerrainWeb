#ifndef _ASYN_CON_H_
#define _ASYN_CON_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/beast/http.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/property_tree/ptree.hpp>
#include <nlohmann/json.hpp>

#include "../core/data_access/postgres/postgres_init/postgres.h"

using namespace boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using ip::tcp;
using json = nlohmann::json;
using ptree = boost::property_tree::ptree;

class tcp_connection: public boost::enable_shared_from_this<tcp_connection>
{
    private:
        tcp::socket __socket;
        std::string __message;
        http::request<http::string_body> __request;
        char __data[1024];
        std::string __response_buffer;

        Postgres __postgres;                            //postgres database

        http::response<http::buffer_body> __form_htpp_response_code(int &code_error);
        bool __define_target_url(int &id, std::string &category);
        void __define_category(std::string &category);
        int __define_user_id();

        std::string __handle_get_request(int &http_response_code);
        bool __handle_post_request(int &http_response_code);
        bool __handle_patch_request(int &http_response_code);
        bool __handle_put_request(int &http_response_code);

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
