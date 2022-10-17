#ifndef _INTERFACE_USERS_DB_H_
#define _INTERFACE_USERS_DB_H_

#include "../users/users_struct.h"

class IUsersDb
{
    public:
        IUsersDb() = default;
        virtual ~IUsersDb() = default;

        virtual int get(int &id, users_t &user) = 0;
        virtual int add(users_t &user) = 0;
        virtual int delete_user(int &id) = 0;
        virtual int update(int &id, users_t &user) = 0;
        virtual int block(int &id) = 0;
        virtual int unlock(int &id) = 0;
};

#endif
