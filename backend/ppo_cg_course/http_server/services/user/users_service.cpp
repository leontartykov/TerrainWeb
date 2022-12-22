#include "users_service.hpp"
#include "error_codes.h"

UsersService::UsersService(std::shared_ptr<DbModel> dbModel)
{
    set_dbModel(dbModel);
}

UsersService::~UsersService()
{
    std::cerr << "UserServise Destructor\n";
}

void UsersService::set_dbModel(std::shared_ptr<DbModel> dbModel){
    __dbModel = dbModel;
}

int UsersService::get(const int &id, servUsers_t &user){
    return __dbModel->get_user(id, user);
}

int UsersService::add(const servUsers_t &user){
     return __dbModel->add_user(user);
}

int UsersService::delete_user(const int &id){
    return __dbModel->delete_user(id);
}

int UsersService::update(const int &id, const servUsers_t &user){
    return __dbModel->update_user(id, user);
}

int UsersService::block(const int &id){
    return __dbModel->block_user(id);
}

int UsersService::unlock(const int &id){
    return __dbModel->unlock_user(id);
}

int UsersService::validate(const servUsers_t &user, int &uuid){
    return __dbModel->login(user.login, user.password, uuid);
}

int UsersService::login(std::string &access_token, int &uuid){
    int ret_code = SUCCESS;
    JWTUser jwt_user;

    access_token = jwt_user.create_token();
    __sessions.add(uuid, access_token);

    return ret_code;
}

int UserSessions::check_usr_authorization(std::string &token, int &uuid)
{
    int success = SUCCESS;

    try{
        if (!token.empty()){
            success = this->check_access_token(uuid, token);
        }
        else{
            success = BAD_REQUEST;
        }
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        success = BAD_REQUEST;
        return success;
    }

    std::cerr << "success_check: " << success << "\n";
    return success;
}
