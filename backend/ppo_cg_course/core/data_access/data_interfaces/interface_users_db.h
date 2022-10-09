#ifndef _INTERFACE_USERS_DB_H_
#define _INTERFACE_USERS_DB_H_

#include "../users/users_struct.h"

class IUsersDb
{
    public:
        IUsersDb() = default;
        virtual ~IUsersDb() = default;

        virtual users_t get_by_id(int id);
        virtual int add(users_t &user);
        virtual int delete_user(int id);
        virtual int update_login(int id, std::string new_login);
        virtual int block(std::string login);
        virtual int unlock(std::string login);
};

#endif
