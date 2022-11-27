#ifndef _USERS_SERVICE_HPP_
#define _USERS_SERVICE_HPP_

#include "core/data_access/postgres/postgres_init/postgres.h"

class UsersService
{
    private:
        Postgres __postgres;

    public:
        int get(int &id, users_t &user);
        int add(users_t &user);
        int delete_user(int &id);
        int update(int &id, users_t &user);
        int block(int &id);
        int unlock(int &id);
        int validate(users_t &user);
};

#endif
