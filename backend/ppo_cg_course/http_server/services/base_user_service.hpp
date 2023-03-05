#ifndef _BASE_USER_SERVICE_
#define _BASE_USER_SERVICE_

#include <memory>

#include "core/data_access/db_model/base_db_model.hpp"

class IUserService
{
    public:
        virtual ~IUserService() {};
        virtual void set_dbModel(std::shared_ptr<DbModel> dbModel) = 0;
        virtual int get(const int &id, servUsers_t &user) = 0;
        virtual int add(const servUsers_t &user) = 0;
        virtual int delete_user(const int &id) = 0;
        virtual int update(const int &id, const servUsers_t &user) = 0;
        virtual int block(const int &id) = 0;
        virtual int unlock(const int &id) = 0;
        virtual int validate(const servUsers_t &user, int &uuid) = 0;
        virtual int login(std::string &access_token, int &uuid) = 0;
};

#endif
