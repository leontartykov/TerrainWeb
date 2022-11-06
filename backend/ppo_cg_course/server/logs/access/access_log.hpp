#ifndef _ACCESS_LOG_HPP_
#define _ACCESS_LOG_HPP_

#include <fstream>

#define ACCESS_LOG_PATH "../logs/logs_server/access.log"

class ServerAccessLog
{
    private:
        std::ofstream __access_log_file;

    public:
        ServerAccessLog();
        ~ServerAccessLog();

        bool is_open_log_file();
        bool write_log(std::string &log_info);
};

#endif
