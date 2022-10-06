#ifndef _ASYN_CON_H_
#define _ASYN_CON_H_

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

using namespace boost::asio;
using ip::tcp;

class tcp_connection: public boost::enable_shared_from_this<tcp_connection>
{
    private:
        tcp::socket __socket;
        std::string __message;
        char __data[1024];
    public:
        typedef boost::shared_ptr<tcp_connection> pointer;

        static pointer create(io_service &io_context);
        tcp_connection(io_service &io_context);

        void start();
        void handle_write(const boost::system::error_code &error, size_t bytes_transferred);
        void handle_read(const boost::system::error_code &error, size_t bytes_transferred);
        tcp::socket &socket();
};

#endif
