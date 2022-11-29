#ifndef _USERS_SERVICE_HPP_
#define _USERS_SERVICE_HPP_

#include "core/data_access/db_model/postgres/postgres.hpp"

class UsersService
{
    private:
        Postgres __postgres;

    public:
        int get(int &id, dbUsers_t &user);
        int add(dbUsers_t &user);
        int delete_user(int &id);
        int update(int &id, dbUsers_t &user);
        int block(int &id);
        int unlock(int &id);
        int validate(dbUsers_t &user);
};

#endif
