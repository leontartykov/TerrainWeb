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
    async_write(__socket, buffer(__message), boost::bind(&tcp_connection::handle_write, shared_from_this(),
                                                         boost::asio::placeholders::error,
                                                         boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::handle_write(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error) {
       std::cout << "Server sent Hello message!\n";
    } else {
       std::cerr << "error: " << error.message() << "\n";
       __socket.close();
    }
}

void tcp_connection::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
  {
    if (!error) {
         std::cout << __data << "\n";
    } else {
         std::cerr << "error: " << error.message() << std::endl;
         __socket.close();
    }
  }
