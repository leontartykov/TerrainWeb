#include "users_service.hpp"

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

int UsersService::get(const int &id, dbUsers_t &user){
    return __dbModel->get_user(id, user);
}

int UsersService::add(const dbUsers_t &user){
    return __dbModel->add_user(user);
}

int UsersService::delete_user(const int &id){
    return __dbModel->delete_user(id);
}

int UsersService::update(const int &id, const dbUsers_t &user){
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
