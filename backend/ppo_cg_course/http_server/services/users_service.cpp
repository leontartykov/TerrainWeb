#include "users_service.hpp"

int UsersService::get(int &id, dbUsers_t &user){
    return __postgres.get_user(id, user);
}

int UsersService::add(dbUsers_t &user){
    return __postgres.add_user(user);
}

int UsersService::delete_user(int &id){
    return __postgres.delete_user(id);
}

int UsersService::update(int &id, dbUsers_t &user){
    return __postgres.update_user(id, user);
}

int UsersService::block(int &id){
    return __postgres.block_user(id);
}

int UsersService::unlock(int &id){
    return __postgres.unlock_user(id);
}

int UsersService::validate(dbUsers_t &user){
    return __postgres.check_validation(user);
}
