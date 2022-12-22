#include "http_server/controllers/http_controllers.hpp"
#include "http_server/controllers/form_http_response.hpp"
#include "core/config/config.h"
#include "error_codes.h"

api::v1::TerrainsController::TerrainsController(){
    __terrains_service = std::make_shared<TerrainsService>();
    //__config = std::make_shared<Config>();

    config_t config = __config.read_config_postgres();

    __terrains_service->set_dbModel(create_db_model(config));

}

/*void api::v1::TerrainsController::set_dbModel(std::shared_ptr<DbModel> dbModel){
    __terrains_service->set_dbModel(dbModel);
}*/

void api::v1::TerrainsController::get_all_terrain_projects(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userId, std::string page)
{
    int user_id, uuid, ret_code, pageBlock;
    std::vector<servTerrainProject_t> terProjects;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::cerr <<"get_all_ter_projs\n";
    std::cerr <<"page: " << page << "\n";

    try{
        /*token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
        */
            user_id = std::stoi(userId);
            pageBlock = std::stoi(page);
            std::cerr << "pageBlock: " << pageBlock << "\n";
            ret_code = __terrains_service->get_terrain_projects(user_id, pageBlock, terProjects);
            jsonBody = form_json_response(terProjects);

            resp = form_http_response(ret_code, jsonBody);
        //}
        callback(resp);
    }
    catch (std::exception &e) {
        std::cout << e.what();
        ret_code = FORBIDDEN;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::add_new_project(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userId)
{
    int ret_code, user_id, uuid;
    json json_get;
    std::string terProjName;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::cerr << "here_add_params\n";

    try
    {
        /*token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{*/
            user_id = std::stoi(userId);
            json_get = json::parse(req->bodyData());
            terProjName = json_get["name"];
            std::cerr << "terProjName: " << terProjName << "\n";
            ret_code = __terrains_service->add_terrain_project(user_id, terProjName);

            resp = form_http_response(ret_code, jsonBody);
        //}
        callback(resp);
    }
    catch (std::exception &e){
        std::cout << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::get_terrain_params(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userId, std::string terrainId)
{
    int user_id, terrain_id, ret_code, uuid;
    servTerrain_t terrain;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;


    try {
        std::cerr << "here_get_params\n";
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            user_id = std::stoi(userId);
            terrain_id = std::stoi(terrainId);

            ret_code = __terrains_service->get_terrain_params(user_id, terrain_id, terrain);
            jsonBody = form_json_response(terrain);
            resp = form_http_response(ret_code, jsonBody);
        }

        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::find_project(
        const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,
        std::string userId, std::string projName)
{
    int user_id, ret_code;
    drogon::HttpResponsePtr resp;
    servTerrainProject_t project;
    std::cerr << "FIND_PROJECT\n";

    Json::Value jsonBody;
    try{
        user_id = std::stoi(userId);
        ret_code = __terrains_service->get_terrain_project(user_id, projName, project);
        std::cerr << "SERV_RET_CODE: " << ret_code << "\n";
        jsonBody = form_json_response(project);
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::delete_terrain_project(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userId, std::string projName)
{
    int user_id, terrain_id, ret_code, uuid;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::cerr << "DELETE\n";

    try{
        std::cerr << "here_del_params\n";
        /*token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{*/
            user_id = std::stoi(userId);
            ret_code = __terrains_service->delete_terrain_project(user_id, projName);
            resp = form_http_response(ret_code, jsonBody);
        //}

        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::get_rating_terrain_project(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string terrainId)
{
    int terrain_id, ret_code, uuid;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    double rating;

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            terrain_id = std::stoi(terrainId);
            ret_code = __terrains_service->get_terrain_project_rating(terrain_id, rating);
            jsonBody = form_json_response(rating);

            resp = form_http_response(ret_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
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
            response_code = FORBIDDEN;
            resp = form_http_response(response_code, jsonBody);
        }
        else{
            terrain_id = std::stoi(terrainId);
            json = req.get()->getJsonObject();

            rating = (*json)["rating"].asInt();
            response_code = __terrains_service->set_terrain_project_rating(terrain_id, rating);
            resp = form_http_response(response_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        response_code = BAD_REQUEST;;
        resp = form_http_response(response_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::get_render_image(
        const HttpRequestPtr &req,
        std::function<void (const HttpResponsePtr &)> &&callback)
{
    int ret_code, uuid;
    Json::Value jsonBodyout;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::pair<dbTerrain_t, light_t> scene_info;
    std::shared_ptr<Json::Value> jsonBodyIn;
    std::string filename = "images/fee.png";
    std::cerr << "RENDER_JOBS\n";

    try{
        /*token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBodyout);
        }
        else{*/
            jsonBodyIn = req.get()->getJsonObject();
            scene_info = __handle_json_body(jsonBodyIn);
            ret_code = __terrains_service->get_render_png_image(scene_info.first, scene_info.second);
            std::cerr << "ret_code: " << ret_code << "\n";
            resp = form_http_response(ret_code, filename);
        //}
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBodyout);
        callback(resp);
    }
}

std::pair<dbTerrain_t, light_t>
    api::v1::TerrainsController::__handle_json_body(std::shared_ptr<Json::Value> jsonBodyIn)
{
    dbTerrain_t terrain;
    light_t light;

    std::cerr << "width: " << (*jsonBodyIn)["terrain"]["size"]["width"] <<"\n";
    terrain.width = (*jsonBodyIn)["terrain"]["size"]["width"].asInt();
    std::cerr << "terrain.width: " << terrain.width << "\n";
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
    std::cerr << "terrain.rotate_angles.angle_z: " << terrain.rotate_angles.angle_z << "\n";
    light.x = (*jsonBodyIn)["light"]["x"].asInt();
    light.y = (*jsonBodyIn)["light"]["y"].asInt();
    light.z = (*jsonBodyIn)["light"]["z"].asInt();


    return {terrain, light};
}
