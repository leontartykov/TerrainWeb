#ifndef _JSON_FORMER_HPP_
#define _JSON_FORMER_HPP_

#include <drogon/HttpController.h>

#include "core/data_access/db_model/postgres/postgres_data/postgres_terrains/postgres_terrains.h"
#include "core/data_access/db_model/postgres/postgres_data/postgres_users/postgres_user.h"
#include "http_server/services/terrain/terrains_service.hpp"

Json::Value form_json_response(servUsers_t &user);
Json::Value form_json_response(std::vector<servTerrainProject_t> &ter_projs);
Json::Value form_json_response(const servTerrain_t &terrain);
Json::Value form_json_response(const servTerrainProject_t &ter_proj);
Json::Value form_json_response(std::string &token, int &user_id);
Json::Value form_json_response(double &terProjRating);

#endif // JSON_FORMER_H
