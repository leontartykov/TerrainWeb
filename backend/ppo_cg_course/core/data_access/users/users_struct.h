#ifndef _USERS_STRUCT_H_
#define _USERS_STRUCT_H_

#include <iostream>

typedef struct users users_t;
struct users{
    std::string login, password;
    std::string is_blocked; //false if is unblocked, true -- if blocked
    std::string is_deleted;
};

#endif
