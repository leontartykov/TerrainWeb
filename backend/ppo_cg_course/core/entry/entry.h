#ifndef _ENRTY_H_
#define _ENRTY_H_

#include <iostream>
#include <pqxx/pqxx>
#include <memory>
#include "../data_access/users/admin/admin.h"
#include "../data_access/users/user/users.h"
#include "../config/config.h"

typedef struct user_info user_info_t;
struct user_info{
    std::string login;
    std::string password;
};

enum menu{
    QUIT,
    LAUNCH,
    ADD_USER,
    DELETE_USER,
    LOCK_USER,
    UNLOCK_USER
};

class EntrySystem
{
    public:
        EntrySystem();
        ~EntrySystem();

        int enter_system();
        config_t get_config_data();

    private:
        int _verify_user(user_info_t &user);
        std::unique_ptr<pqxx::connection> _connect;
        time_t _current_time;
        Config _config;
        std::string _form_options(config_t &config_data);
};

#endif
