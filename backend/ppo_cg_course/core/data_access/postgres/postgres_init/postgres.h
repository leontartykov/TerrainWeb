#ifndef _POSTGRES_H_
#define _POSTGRES_H_

#include "../postgres_data/postgres_users/postgres_user.h"
#include "../../../config/config.h"

enum users_action{
    add,
    get,
    update,
    delete_user,
    block,
    unlock
};

class Postgres
{
    private:
        std::unique_ptr<UserPostgres> __users;                           //postgres's user management
        Config __config;                                //configure launch postgres database

        std::shared_ptr<pqxx::connection> __connection; //postgres's connection
        int __connect_psql_to_db();

    public:
        Postgres();
        ~Postgres() = default;

        void set_psql_connection(std::shared_ptr<pqxx::connection> &connection);
        int do_action_users(const users_action &action, users_t &user);
        int get_count_users();
};

#endif
