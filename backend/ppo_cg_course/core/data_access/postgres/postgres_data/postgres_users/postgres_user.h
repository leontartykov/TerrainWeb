#ifndef _POSTGRES_USERS_H_
#define _POSTGRES_USERS_H_

#include <pqxx/pqxx>
#include "../../../data_interfaces/interface_users_db.h"

class UserPostgres: public IUsersDb
{
    private:
        int __count_users;
        users_t __user_data;
        std::shared_ptr<pqxx::connection> __conn_psql;

        void __disconnect_db();
        bool __is_user_empty(users_t &user);

    public:
        UserPostgres();
        ~UserPostgres() = default;

        virtual users_t get(int &id) override;
        virtual int add(users_t &user) override;
        virtual int delete_user(int &id) override;
        virtual int update_login(int &id, std::string &new_login) override;
        virtual int block(int &id) override;
        virtual int unlock(int &id) override;

        int __connect_psql_to_db();
        void set_psql_connection(std::shared_ptr<pqxx::connection> &conn_psql);
        users_t get(int &id, std::string &schema_name);
};

#endif
