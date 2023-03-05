#ifndef _BUILDERS_HPP_
#define _BUILDERS_HPP_

#include <memory>
#include "http_server/services/user/struct_users_service.hpp"

class UserBuilder
{
    private:
        servUsers_t __user;

    public:
        UserBuilder() = default;
        UserBuilder(servUsers_t user)
        {
            __user.login = user.login;
            __user.password = user.password;
            __user.perm_level = user.perm_level;
        }


        std::unique_ptr<UserBuilder> BuildDefault()
        {
            servUsers_t user;
            user.login = "default";
            user.password = "default";
            user.perm_level = 2;

            return std::make_unique<UserBuilder>(user);
        };

        servUsers_t getUser() const{
            return __user;
        }
};

#endif
