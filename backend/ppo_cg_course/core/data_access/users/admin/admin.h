#ifndef _ADMIN_H_
#define _ADMIN_H_

#include <pqxx/pqxx>
#include <vector>
#include <memory>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_driver.h>
#include <string>

#include "../base_user.h"
#include "core/entry/entry.h"
#include "core/entry/app_facade/app_facade.h"
#include "../users_struct.h"
#include "core/config/config.h"
#include "core/data_access/db_model/postgres/postgres_data/postgres_users/postgres_user.h"
#include "core/data_access/db_model/postgres/postgres_data/postgres_terrains/postgres_terrains.h"
#include "core/data_access/db_model/postgres/postgres.hpp"

class Admin: public BaseAppUser
{
    private:
        std::shared_ptr<pqxx::connection> _connect_psql;
        sql::Connection *_connect_mysql;

        Postgres __postgres;
        TerrainProjectsPostgres __terrain_projects_psql;

        std::vector<dbUsers_t> _users;

        std::shared_ptr<AppFacade> _app_facade;

        int _connect_psql_to_db();
        int _connect_mysql_to_db();
        int __add_user_psql(const servUsers_t &user);
        int _add_user_mysql(servUsers_t &user);

        int __delete_user_psql(const int &userId);
        int _delete_user_mysql(servUsers_t &user);

        void show_menu();
        time_t _current_time;
        Config _config;

        int __delete_user_psql(const std::string &login);

    public:
        Admin();
        ~Admin();

        int add_user(const servUsers_t &user);
        int delete_user(const int &userId);
        int delete_user(const std::string &login);
        int lock_user(const servUsers_t &user);
        int unlock_user(const servUsers_t &user);
        int disconnect_db();
        int check_connection();

        virtual int do_action() override;
        virtual void set_user_login(std::string &usr_login) override;
};

#endif
