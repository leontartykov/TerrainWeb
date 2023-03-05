#ifndef _USERS_SERVICE_HPP_
#define _USERS_SERVICE_HPP_



#include "http_server/services/base_user_service.hpp"

#include "core/data_access/redis/sessions.hpp"
#include "server/jwt/jwt.hpp"

class UserSessions: public RedisSessions {
    public:
        int check_usr_authorization(std::string &token, int &uuid);
};

class UsersService: public IUserService
{
    private:
        UserSessions __sessions;
        std::shared_ptr<DbModel> __dbModel;

    public:
        UsersService() = default;
        UsersService(std::shared_ptr<DbModel> dbModel);
        virtual ~UsersService() override;

        virtual void set_dbModel(std::shared_ptr<DbModel> dbModel) override;
        virtual int get(const int &id, servUsers_t &user) override;
        virtual int add(const servUsers_t &user) override;
        virtual int delete_user(const int &id) override;
        virtual int update(const int &id, const servUsers_t &user) override;
        virtual int block(const int &id) override;
        virtual int unlock(const int &id) override;
        virtual int validate(const servUsers_t &user, int &uuid) override;
        virtual int login(std::string &access_token, int &uuid) override;
};

#endif
