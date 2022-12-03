#ifndef _POSTGRES_USERS_H_
#define _POSTGRES_USERS_H_

#include <pqxx/pqxx>

#include "core/data_access/data_interfaces/interface_users_db.h"
#include "error_codes.h"

class UserPostgres: public IUsersDb
{
    private:
        int __count_users;
        dbUsers_t __user_data;
        std::shared_ptr<pqxx::connection> __conn_psql;

        void __disconnect_db();
        bool __is_user_empty(const dbUsers_t &user);
        void __define_count_users();

    public:
        UserPostgres() = default;
        UserPostgres(std::shared_ptr<pqxx::connection> &conn_psql);
        ~UserPostgres() = default;

        virtual int get(const int &id, dbUsers_t &user) override;
        virtual int add(const dbUsers_t &user) override;
        virtual int delete_user(const int &id) override;
        virtual int update(const int &id, const dbUsers_t &user) override;
        virtual int block(const int &id) override;
        virtual int unlock(const int &id) override;

        int get_validation(dbUsers_t &user);

        void set_psql_connection(std::shared_ptr<pqxx::connection> &conn_psql);
        int get_count_users();
};

#endif
