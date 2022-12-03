#ifndef _STRUCT_USERS_SERVICE_
#define _STRUCT_USERS_SERVICE_

#include <iostream>

typedef struct servUsers servUsers_t;
struct servUsers{
    int id;
    std::string login;
    std::string password;
    int perm_level;
    std::string is_blocked; //false if is unblocked, true -- if blocked
    std::string is_deleted; //false if is not deleted, true -- if deleted
};

#endif
