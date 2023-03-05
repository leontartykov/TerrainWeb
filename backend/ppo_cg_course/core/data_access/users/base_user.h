#ifndef _BASE_USER_H_
#define _BASE_USER_H_

#include <iostream>

class BaseAppUser
{
    public:
        virtual ~BaseAppUser() {};

        virtual int do_action() = 0;
        virtual void set_user_login(std::string &usr_login) = 0;

    protected:
        std::string user_login;
};

#endif
