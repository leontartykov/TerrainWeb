#ifndef _JSON_FORMER_HPP_
#define _JSON_FORMER_HPP_

#include <nlohmann/json.hpp>
#include <vector>
#include <core/data_access/db_model/postgres/postgres_data/postgres_terrains/postgres_terrains.h>
#include <core/data_access/db_model/postgres/postgres_data/postgres_users/postgres_user.h>

using json = nlohmann::json;

json form_json_response(std::vector<terrain_project_t> &ter_projs);
json form_json_response(terrain_project_t &ter_proj);
json form_json_response(users_t &user);
json form_json_response(std::string token, int &user_id);

#endif // JSON_FORMER_H
