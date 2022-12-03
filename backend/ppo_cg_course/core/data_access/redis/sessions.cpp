#include "sessions.hpp"
#include <iostream>

RedisSessions::RedisSessions(): __redis(Redis("tcp://127.0.0.1:6379")){
    __usr_hash = "usr:";
}

///Add info {accessToken: string}
void RedisSessions::add(int &user_id, std::string access_token)
{
    std::unordered_map<std::string, std::string> m;
    m = {{"access_token", access_token}, {"EX", "60"}};
    __usr_hash = __usr_hash + std::to_string(user_id);

    __redis.hmset(__usr_hash, m.begin(), m.end());
    __redis.expire(__usr_hash, 3000);
}

///Check correctness access token
int RedisSessions::check_access_token(int &user_id, std::string token)
{
    int success = FORBIDDEN;
    std::string db_token;
    db_token = __get_access_token(user_id);

    if (token.compare(db_token) == 0){
       success = SUCCESS;
    }
    std::cerr << "success: " << success << "\n";

    return success;
}

///Return user session info {accessToken: string}
std::string RedisSessions::__get_access_token(int &user_id)
{
    std::unordered_map<std::string, std::string> m;
    std::string usr_access;

    __usr_hash = "usr:" + std::to_string(user_id);
    __redis.hgetall(__usr_hash, std::inserter(m, m.begin()));

    return m["access_token"].c_str();
}
