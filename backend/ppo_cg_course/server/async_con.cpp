#include "async_con.h"
#include <boost/beast/version.hpp>

tcp_connection::tcp_connection(io_service &io_context): __socket(io_context){}

tcp_connection::pointer tcp_connection::create(io_service &io_context){
    return pointer(new tcp_connection(io_context));
}

tcp::socket &tcp_connection::socket(){
    return __socket;
}

void tcp_connection::start()
{
    handle_read();
    /*boost::asio::async_read_until(__socket, boost::asio::dynamic_buffer(__message), "\n",
                                  boost::bind(&tcp_connection::handle_read, this,
                                              boost::asio::placeholders::error,
                                              boost::asio::placeholders::bytes_transferred));*/

    //auto bytes = read_until(__socket, boost::asio::dynamic_buffer(__message), "\r\n");
    //std::cout << __message.substr(0, bytes) << std::flush;

}

void tcp_connection::handle_write(const boost::system::error_code& error, size_t bytes_transferred)
{
    std::cout << "Message from client was received.n";
    if (!error) {
       std::cout << "Server sent Hello message!\n";
    } else {
       std::cerr << "error: " << error.message() << "\n";
       __socket.close();
    }
}

http::response<http::buffer_body> tcp_connection::__form_htpp_response_code(int &code_error)
{
    http::response<http::buffer_body> response;
    if (code_error == 0 || code_error == 200){
        response.result(http::status::ok);
    }
    else if (code_error == 400){
        response.result(http::status::bad_request);
    }
    else if (code_error == 403){
        response.result(http::status::forbidden);
    }
    else if (code_error == 404){
        response.result(http::status::not_found);
    }

    response.version(__request.version());
    response.set(http::field::server, "Terrain Server");
    response.set("Access-Control-Allow-Methods", "GET, DELETE, PUT, POST, PATCH");
    response.set("Access-Control-Allow-Origin", "*");
    response.set("Access-Control-Allow-Headers", "Accept, Authorization, Cache-Control, \
                 Content-Type, DNT, If-Modified-Since, Keep-Alive, Origin, User-Agent, X-Requested-With");
    response.keep_alive(__request.keep_alive());

    if (!__response_buffer.empty())
    {
        std::cout << "non-empty response body.\n";
        response.set(beast::http::field::content_type, "application/json");
        response.content_length(strlen(__response_buffer.c_str()));
        std::cout << __response_buffer.c_str();

        response.body().data = (void *)__response_buffer.c_str();
        response.body().size = strlen(__response_buffer.c_str());
        response.body().more = false;
    }
    else{
        response.content_length(0);
        response.body().more = false;
        std::cout << "empty response body.\n";
    }

    return response;
}

bool tcp_connection::handle_read()
{
    int http_response_code;
    streambuf buf;
    http::read(__socket, buf, __request);

    //ВЫНЕСТИ ПРОВЕРКУ __request ОТДЕЛЬНО
    http::verb method = __request.method();
    std::cerr << "method: " << __request.method_string().data() << "\n";
    http::response<http::buffer_body> response;

    switch (method)
    {
        case http::verb::unknown:
            std::cout << "неизвестный запрос.\n";
            break;
        case http::verb::get:
            __response_buffer = __handle_get_request(http_response_code);
            response = __form_htpp_response_code(http_response_code);
            http::write(__socket, response);
            /*async_write(__socket, buffer(return_request.str()),
                        boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                    boost::asio::placeholders::error,
                                    boost::asio::placeholders::bytes_transferred));*/

            break;
        case http::verb::post:
            __handle_post_request(http_response_code);
            response = __form_htpp_response_code(http_response_code);
            http::write(__socket, response);
            break;
        case http::verb::put:
            __handle_put_request(http_response_code);
            std::cout << "пока нет функционала для этого запроса PUT.\n";
            break;
        case http::verb::patch:
            __handle_patch_request(http_response_code);
            response = __form_htpp_response_code(http_response_code);
            http::write(__socket, response);
            break;
        case http::verb::options:
            response = __form_htpp_response_code(http_response_code);
            http::write(__socket, response);
            break;
        case http::verb::head:
            std::cout << "пока нет функционала для этого запроса HEAD.\n";
            break;
        default:
            std::cout << "пока нет функционала для этого запроса.\n";
            break;
    }

    return true;
}
