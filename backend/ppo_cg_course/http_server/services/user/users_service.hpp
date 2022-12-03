#ifndef _USERS_SERVICE_HPP_
#define _USERS_SERVICE_HPP_

#include <memory>
#include "core/data_access/db_model/base_db_model.hpp"

class UsersService
{
    private:
        std::shared_ptr<DbModel> __dbModel;

    public:
        UsersService() = default;
        UsersService(std::shared_ptr<DbModel> dbModel);
        ~UsersService();

        void set_dbModel(std::shared_ptr<DbModel> dbModel);
        int get(const int &id, dbUsers_t &user);
        int add(const dbUsers_t &user);
        int delete_user(const int &id);
        int update(const int &id, const dbUsers_t &user);
        int block(const int &id);
        int unlock(const int &id);
        int validate(const servUsers_t &user, int &uuid);
};

#endif
