#ifndef _ENRTY_H_
#define _ENRTY_H_

#include <iostream>
#include <pqxx/pqxx>
#include <memory>
#include "core/data_access/users/admin/admin.h"
#include "core/data_access/users/user/users.h"
#include "core/config/config.h"
#include "http_server/services/user/struct_users_service.hpp"
#include "core/data_access/db_model/base_db_model.hpp"
#include "core/data_access/db_model/postgres/postgres.hpp"

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
    private:
        std::shared_ptr<DbModel> __dbModel;
        int _verify_user(user_info_t &user);
        std::unique_ptr<pqxx::connection> _connect;
        time_t _current_time;
        Config _config;
        std::string _form_options(config_t &config_data);
        servUsers_t __input_user_info();

    public:
        EntrySystem();
        ~EntrySystem();

        int enter_system();
        config_t get_config_data();

};

#endif
