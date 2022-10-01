#ifndef _CONFIG_STRUCT_H_
#define _CONFIG_STRUCT_H_

#include <iostream>

typedef struct config config_t;
struct config
{
    std::string dbms_type;
    std::string host;
    std::string port;
    std::string user;
    std::string password;
    std::string db_name;
};

#endif
