#ifndef _USER_SOLUTION_HPP_
#define _USER_SOLUTION_HPP_

#include <map>
#include "../../data_access/users/users.h"

class UsersCreator{
    public:
        virtual ~UsersCreator() = default;
        virtual std::unique_ptr<NBaseUser> create_user() = 0;
};

template <typename TUser>
class UserCreator: public UsersCreator
{
    public:
        virtual std::unique_ptr<BaseUser> create_user() override{
            return std::unique_ptr<BaseUser>(new TUser());
        }
};

std::unique_ptr<UsersCreator> create_admin_creator(){
    return std::unique_ptr<UsersCreator>(new UserCreator<Admin>());
}

/*std::unique_ptr<UsersCreator> create_user_creator(){
    return std::unique_ptr<UsersCreator>(new UserCreator<User>());
}*/

class UserSolution
{
    public:
        typedef std::unique_ptr<UsersCreator> (*CreateCreator)();

        bool registration(size_t id, CreateCreator create_user){
            return _users_map.insert(UserMap::value_type(id, create_user)).second;
        }

        std::unique_ptr<UsersCreator> create(size_t id){
            UserMap::const_iterator it = _users_map.find(id);

            if (it == _users_map.end()){
                std::cout << "Не найдено.";
            }

            return std::unique_ptr<UsersCreator>((it->second)());
        }

    private:
        using UserMap = std::map<size_t, CreateCreator>;
        UserMap _users_map;
};

#endif
