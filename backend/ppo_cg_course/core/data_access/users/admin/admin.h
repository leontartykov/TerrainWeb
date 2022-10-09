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
#include "../../../entry/entry.h"
#include "../../../entry/app_facade/app_facade.h"
#include "../users_struct.h"
#include "../../../config/config.h"
#include "../../postgres_data/postgres_users/postgres_user.h"
#include "../../postgres_data/postgres_terrains/postgres_terrains.h"

class Admin: public BaseUser
{
    private:
        std::unique_ptr<pqxx::connection> _connect_psql;
        sql::Connection *_connect_mysql;

        UserPostgres __users_psql;
        TerrainProjectsPostgres __terrain_projects_psql;

        std::vector<users_t> _users;

        std::shared_ptr<AppFacade> _app_facade;

        int _connect_psql_to_db();
        int _connect_mysql_to_db();
        int __add_user_psql(users_t &user);
        int _add_user_mysql(users_t &user);

        int __delete_user_psql(int id);
        int _delete_user_mysql(users_t &user);

        void show_menu();
        time_t _current_time;
        Config _config;
    public:
        Admin();
        ~Admin();

        int add_user(users_t &user);
        int delete_user(int id);
        int lock_user(std::string login);
        int unlock_user(std::string login);
        int disconnect_db();
        int check_connection();

        virtual int do_action() override;
        virtual void set_user_login(std::string &usr_login) override;
};

#endif
