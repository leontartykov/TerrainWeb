#ifndef _USERS_STRUCT_H_
#define _USERS_STRUCT_H_

#include <iostream>

typedef struct users users_t;
struct users{
    int id;
    std::string login;
    std::string password;
    int perm_level;
    std::string is_blocked; //false if is unblocked, true -- if blocked
    std::string is_deleted; //false if is not deleted, true -- if deleted
};

#endif
