#ifndef _LOG_STRUCTS_H_
#define _LOG_STRUCTS_H_

#include <iostream>

typedef struct log_info log_info_t;
struct log_info
{
    std::string type_log;
    std::string file_name;
    std::string class_name;
    std::string function_name;
    int line_error;
    const char *time_error;
    std::string message_error;
    int number_error;
    std::string user_login;
};

#endif
