#ifndef _USERS_H_
#define _USERS_H_

#include <iostream>
#include "core/data_access/users/base_user.h"
#include "core/entry/entry.h"
#include "core/entry/app_command/app_command.h"
#include "core/entry/app_facade/app_facade.h"

class User: public BaseAppUser
{
    private:
        std::shared_ptr<AppFacade> _app_facade;
        void show_menu();
        time_t _current_time;

    public:
        User();
        ~User() = default;

        virtual int do_action() override;
        virtual void set_user_login(std::string &usr_login) override;
};

#endif
