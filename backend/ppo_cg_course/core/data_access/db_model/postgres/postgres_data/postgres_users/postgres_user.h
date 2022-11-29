#ifndef _POSTGRES_USERS_H_
#define _POSTGRES_USERS_H_

#include <pqxx/pqxx>
#include "core/data_access/data_interfaces/interface_users_db.h"

class UserPostgres: public IUsersDb
{
    private:
        int __count_users;
        dbUsers_t __user_data;
        std::shared_ptr<pqxx::connection> __conn_psql;

        void __disconnect_db();
        bool __is_user_empty(dbUsers_t &user);
        void __define_count_users();

    public:
        UserPostgres() = default;
        UserPostgres(std::shared_ptr<pqxx::connection> &conn_psql);
        ~UserPostgres() = default;

        virtual int get(int &id, dbUsers_t &user) override;
        virtual int add(dbUsers_t &user) override;
        virtual int delete_user(int &id) override;
        virtual int update(int &id, dbUsers_t &user) override;
        virtual int block(int &id) override;
        virtual int unlock(int &id) override;

        bool check_validation(dbUsers_t &user);

        void set_psql_connection(std::shared_ptr<pqxx::connection> &conn_psql);
        dbUsers_t get(int &id, std::string &schema_name);
        int get_count_users();
};

#endif
