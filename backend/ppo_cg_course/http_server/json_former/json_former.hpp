#ifndef _JSON_FORMER_HPP_
#define _JSON_FORMER_HPP_

#include <nlohmann/json.hpp>
#include <core/data_access/postgres/postgres_data/postgres_terrains/postgres_terrains.h>
#include <core/data_access/postgres/postgres_data/postgres_users/postgres_user.h>
#include <drogon/HttpController.h>

using json = nlohmann::json;

json form_json_response_new(std::vector<terrain_project_t> &ter_projs);
json form_json_response_new(terrain_project_t &ter_proj);
json form_json_response_new(users_t &user);
json form_json_response_new(std::string token, int &user_id);

Json::Value form_json_response(users_t &user);
Json::Value form_json_response(std::vector<terrain_project_t> &ter_projs);
Json::Value form_json_response(terrain_project_t &ter_proj);
Json::Value form_json_response(std::string &token, int &user_id);
Json::Value form_json_response(double &terProjRating);

#endif // JSON_FORMER_H
