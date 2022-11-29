#include "http_server/controllers/http_controllers.hpp"
#include "http_server/controllers/form_http_response.hpp"
#include "server/server_codes.h"

void api::v1::TerrainsController::get_all_terrain_projects(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userId)
{
    int user_id, uuid, response_code;
    std::pair<int, std::vector<terrain_project_t>> result;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else{
            user_id = std::stoi(userId);
            result = __terrains_service.get_terrain_projects(user_id);
            jsonBody = form_json_response(result.second);

            resp = form_http_response(result.first, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cout << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::add_new_project(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userId)
{
    int response_code, user_id, uuid;
    json json_get;
    std::string ter_proj_name;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else{
            user_id = std::stoi(userId);
            json_get = json::parse(req->bodyData());
            ter_proj_name = json_get["name"];
            response_code = __terrains_service.add_terrain_project(ter_proj_name, user_id);

            resp = form_http_response(response_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e){
        std::cout << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::get_terrain_project_info(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userId, std::string terrainId)
{
    int user_id, terrain_id, response_code, uuid;
    terrain_project ter_proj;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else{
            user_id = std::stoi(userId);
            terrain_id = std::stoi(terrainId);
            ter_proj.id = terrain_id;

            response_code = __terrains_service.get_one_ter_proj(ter_proj, user_id);
            jsonBody = form_json_response(ter_proj);
            resp = form_http_response(response_code, jsonBody);
        }

        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::delete_terrain_project(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userId, std::string terrainId)
{
    int user_id, terrain_id, response_code, uuid;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else{
            user_id = std::stoi(userId);
            terrain_id = std::stoi(terrainId);

            response_code = __terrains_service.delete_terrain_project(user_id, terrain_id);
            resp = form_http_response(response_code, jsonBody);
        }

        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::get_rating_terrain_project(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string terrainId)
{
    int terrain_id, response_code, uuid;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    double rating;

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else{
            response_code = SERV_SUCCESS;
            terrain_id = std::stoi(terrainId);
            rating = __terrains_service.get_terrain_project_rating(terrain_id);
            if (rating == -1){
                response_code = SERV_NOT_FOUND;
            }
            else{
                jsonBody = form_json_response(rating);
            }

            resp = form_http_response(response_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::set_rating_terrain_project(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string terrainId)
{
    int terrain_id, response_code, uuid, rating;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::shared_ptr<Json::Value> json;

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else{
            terrain_id = std::stoi(terrainId);
            json = req.get()->getJsonObject();

            rating = (*json)["rating"].asInt();
            response_code = __terrains_service.set_terrain_project_rating(terrain_id, rating);
            resp = form_http_response(response_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::get_render_image(
        const HttpRequestPtr &req,
        std::function<void (const HttpResponsePtr &)> &&callback)
{
    int response_code, uuid;
    Json::Value jsonBodyout;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::pair<terrain_t, light_t> scene_info;
    std::shared_ptr<Json::Value> jsonBodyIn;
    std::string filename = "images/fee.png";

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        if (!__sessions.check_usr_authorization(token, uuid)){
            response_code = SERV_FORBIDDEN;
            resp = form_http_response(response_code, jsonBodyout);
        }
        else{
            jsonBodyIn = req.get()->getJsonObject();
            scene_info = __handle_json_body(jsonBodyIn);
            response_code = __terrains_service.get_render_png_image(scene_info.first, scene_info.second);
            resp = form_http_response(response_code, filename);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = SERV_BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBodyout);
        callback(resp);
    }
}

std::pair<terrain_t, light_t>
    api::v1::TerrainsController::__handle_json_body(std::shared_ptr<Json::Value> jsonBodyIn)
{
    terrain_t terrain;
    light_t light;

    terrain.width = (*jsonBodyIn)["terrain"]["size"]["width"].asInt();
    terrain.height = (*jsonBodyIn)["terrain"]["size"]["height"].asInt();
    terrain.scale = (*jsonBodyIn)["terrain"]["scale"].asDouble();
    terrain.meta_config.octaves = (*jsonBodyIn)["terrain"]["config"]["octaves"].asInt();
    terrain.meta_config.gain = (*jsonBodyIn)["terrain"]["config"]["gain"].asDouble();
    terrain.meta_config.lacunarity = (*jsonBodyIn)["terrain"]["config"]["lacunarity"].asDouble();
    terrain.meta_config.seed = (*jsonBodyIn)["terrain"]["config"]["seed"].asInt();
    terrain.meta_config.frequency = (*jsonBodyIn)["terrain"]["config"]["frequency"].asDouble();
    terrain.rotate_angles.angle_x = (*jsonBodyIn)["terrain"]["rotate"]["angle_x"].asInt();
    terrain.rotate_angles.angle_y = (*jsonBodyIn)["terrain"]["rotate"]["angle_y"].asInt();
    terrain.rotate_angles.angle_z = (*jsonBodyIn)["terrain"]["rotate"]["angle_z"].asInt();
    light.x = (*jsonBodyIn)["light"]["x"].asInt();
    light.y = (*jsonBodyIn)["light"]["y"].asInt();
    light.z = (*jsonBodyIn)["light"]["z"].asInt();

    return {terrain, light};
}
