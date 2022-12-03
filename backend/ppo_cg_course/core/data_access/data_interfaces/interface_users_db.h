#ifndef _INTERFACE_USERS_DB_H_
#define _INTERFACE_USERS_DB_H_

#include "core/data_access/users/users_struct.h"

class IUsersDb
{
    public:
        IUsersDb() = default;
        virtual ~IUsersDb() = default;

        virtual int get(const int &id, dbUsers_t &user) = 0;
        virtual int add(const dbUsers_t &user) = 0;
        virtual int delete_user(const int &id) = 0;
        virtual int update(const int &id, const dbUsers_t &user) = 0;
        virtual int block(const int &id) = 0;
        virtual int unlock(const int &id) = 0;
};

#endif
