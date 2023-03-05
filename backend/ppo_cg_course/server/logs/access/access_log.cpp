#include <iostream>

#include "access_log.hpp"

ServerAccessLog::ServerAccessLog()
{
    __access_log_file.open(ACCESS_LOG_PATH, std::ios::app);

    if (!__access_log_file.is_open()){
        std::cerr << "Невозможно открыть файл логирования доступа.\n";
    }
}

ServerAccessLog::~ServerAccessLog(){
    __access_log_file.close();
}

bool ServerAccessLog::is_open_log_file(){
    return __access_log_file.is_open();
}

bool ServerAccessLog::write_log(std::string &log_info)
{
    bool success = true;
    if (__access_log_file.is_open()){
        __access_log_file << log_info << "\n";
    }
    else{
        success = false;
    }

    return success;
}
