#ifndef _BUILDERS_HPP_
#define _BUILDERS_HPP_

#include <memory>
#include "core/data_access/db_model/postgres/postgres_data/postgres_users/postgres_user.h"

class UserBuilder
{
    private:
        dbUsers_t __user;

    public:
        UserBuilder() = default;
        UserBuilder(dbUsers_t user)
        {
            __user.login = user.login;
            __user.password = user.password;
            __user.perm_level = user.perm_level;
        }


        std::unique_ptr<UserBuilder> BuildDefault()
        {
            dbUsers_t user;
            user.login = "default";
            user.password = "default";
            user.perm_level = 2;

            return std::make_unique<UserBuilder>(user);
        };

        dbUsers_t getUser() const{
            return __user;
        }
};

#endif
