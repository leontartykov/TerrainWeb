#ifndef SESSIONS_HPP
#define SESSIONS_HPP

#include <sw/redis++/redis++.h>
#include "error_codes.h"

using namespace sw::redis;

class RedisSessions
{
    private:
        Redis __redis;
        std::string __usr_hash;
        std::string __get_access_token(int &user_id);

    public:
        explicit RedisSessions();
        ~RedisSessions() = default;

        void add(int &user_id, std::string access_token);

        int check_access_token(int &user_id, std::string token);
};

#endif // SESSIONS_HPP
