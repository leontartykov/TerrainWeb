#ifndef _ASYN_CON_H_
#define _ASYN_CON_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/beast/http.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/optional/optional_io.hpp>
#include <boost/property_tree/ptree.hpp>

#include "../core/data_access/postgres/postgres_init/postgres.h"
#include "./core/data_access/redis/sessions.hpp"

using namespace boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;
using ip::tcp;

using ptree = boost::property_tree::ptree;

class tcp_connection: public boost::enable_shared_from_this<tcp_connection>
{
    private:
        tcp::socket __socket;
        std::string __message, __response_buffer;
        http::request<http::string_body> __request;
        std::vector<std::string> __url_path_elems;

        Postgres __postgres;                            //postgres database
        UserSessions __sessions;                        //redis sessions

        http::response<http::buffer_body> __form_htpp_response_code(int &code_error);

        bool __define_target_url(int &id, std::string &category);
        std::string __define_category();
        int __define_info_id(std::string info);

        std::string __handle_get_request(int &http_response_code);
        std::string __handle_post_request(int &http_response_code);
        bool __handle_patch_request(int &http_response_code);
        bool __handle_put_request(int &http_response_code);
        bool __handle_delete_request(int &http_response_code);

        int __define_user_id_to_post();
        void __form_url_path_elems();
        bool __check_authorization();


public:
        typedef boost::shared_ptr<tcp_connection> pointer;

        static pointer create(io_service &io_context);
        tcp_connection(io_service &io_context);

        void start();

        void handle_write(http::response<http::buffer_body> &response);
        void handle_read();
        bool handle_request();
        tcp::socket &socket();
};

#endif
