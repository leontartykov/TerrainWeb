#include "async_con.h"

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

bool tcp_connection::handle_read()
{
    bool success = false;
    streambuf buf;
    http::read(__socket, buf, __request);

    //std::string method = request.method_string().data();
    http::verb method = __request.method();
    std::cerr << "method: " << __request.method_string().data() << "\n";

    switch (method)
    {
        case http::verb::unknown:
            std::cout << "неизвестный запрос.\n";
            break;
        case http::verb::get:
            success = __handle_get_request();
            async_write(__socket, buffer(__message),
                        boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                    boost::asio::placeholders::error,
                                    boost::asio::placeholders::bytes_transferred));
            break;
        case http::verb::post:
            success = __handle_post_request();
            break;
        case http::verb::put:
            break;
        default:
            std::cout << "пока нет функционала для этого запроса.\n";
    }

    return success;
    //std::cout <<
}


