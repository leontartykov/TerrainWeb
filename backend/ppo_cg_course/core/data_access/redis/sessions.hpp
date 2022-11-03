#ifndef SESSIONS_HPP
#define SESSIONS_HPP

#include <sw/redis++/redis++.h>

using namespace sw::redis;

class UserSessions
{
    private:
        Redis __redis;
        std::string __usr_hash;
        std::string __get_access_token(int &user_id);

    public:
        explicit UserSessions();
        ~UserSessions() = default;

        void add(int &user_id, std::string access_token);

        bool check_access_token(int &user_id, std::string token);
};

#endif // SESSIONS_HPP
