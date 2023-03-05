#ifndef _JWT_HPP_
#define _JWT_HPP_

#include <iostream>
#include <jwt/jwt_all.h>
#include <openssl/hmac.h>

using json = nlohmann::json;

class JWTUser
{
    private:
        json __payload;

        std::string __create_token();
        std::pair<json, json> __decode(std::string token);

    public:
        JWTUser();
        ~JWTUser() = default;

        std::string create_token();
        std::pair<json, json> decode_token(std::string token);
};

#endif
