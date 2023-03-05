#include "jwt.hpp"
#include <chrono>

JWTUser::JWTUser()
{
    auto need_time = std::chrono::system_clock::now() + std::chrono::seconds{6000};
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(need_time.time_since_epoch()).count();
    __payload = {{"sub", "subject"}, {"exp", time}};
}

std::string JWTUser::create_token(){
    return __create_token();
}

std::pair<json, json> JWTUser::decode_token(std::string token){
    return __decode(token);
}

std::string JWTUser::__create_token(){
    HS256Validator signer("secter");
    return JWT::Encode(signer, __payload);
}

std::pair<json, json> JWTUser::__decode(std::string token){
    ExpValidator exp;
    ::json header, payload;
    HS256Validator signer("secter");
    try
    {
        std::tie(header, payload) = JWT::Decode(token, &signer, &exp);
        std::cout << "Header: " << header << std::endl;
        std::cout << "Payload: " << payload << std::endl;
    }
    catch (InvalidTokenError &tfe) {
       // An invalid token
       std::tie(header, payload) = JWT::Decode(token);
       std::cout << "payload: " << payload << "\n";
       std::cout << "header: " << header << "\n";
       std::cout << "Validation failed: " << tfe.what() << std::endl;
    }

    return {header, payload};
}

