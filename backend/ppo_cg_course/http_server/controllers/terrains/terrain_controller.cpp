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
     std::string userName, std::string page)
{
    int uuid, ret_code, pageBlock;
    std::vector<servTerrainProject_t> terProjects;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try{
        token = req->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            pageBlock = std::stoi(page);
            ret_code = __terrains_service->get_terrain_projects(userName, pageBlock, terProjects);
            jsonBody = form_json_response(terProjects);

            resp = form_http_response(ret_code, jsonBody);
        }
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
     std::string userName)
{
    int ret_code, uuid;
    json json_get;
    std::string terProjName;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::cerr << "here_add_params\n";

    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            json_get = json::parse(req->bodyData());
            terProjName = json_get["name"];
            ret_code = __terrains_service->add_terrain_project(userName, terProjName);

            resp = form_http_response(ret_code, jsonBody);
        }
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
     std::string userName, std::string projName)
{
    int ret_code, uuid;
    servTerrain_t terrain;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try {
        token = req->getHeader("Authorization");
        uuid = std::stoi(req->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            ret_code = __terrains_service->get_terrain_params(userName, projName, terrain);
            jsonBody = form_json_response(terrain);
            resp = form_http_response(ret_code, jsonBody);
        }

        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = FORBIDDEN;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::find_my_project(
        const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,
        std::string userName, std::string projName)
{
    int ret_code, uuid;
    drogon::HttpResponsePtr resp;
    servTerrainProject_t project;
    std::string token;

    Json::Value jsonBody;
    try{
        token = req->getHeader("Authorization");
        uuid = std::stoi(req->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            ret_code = __terrains_service->get_terrain_project(projName, project, userName);
            jsonBody = form_json_response(project);
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

void api::v1::TerrainsController::save_project(const HttpRequestPtr &req,
                                               std::function<void (const HttpResponsePtr &)> &&callback,
                                               std::string userName, std::string projName)
{
    int ret_code, uuid;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::shared_ptr<Json::Value> jsonBodyIn;
    servTerrain_t terrain;

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("UUID"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            jsonBodyIn = req->getJsonObject();
            terrain = __handle_json_Body(jsonBodyIn);
            ret_code = __terrains_service->save_terrain_params(userName, projName, terrain);
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

void api::v1::TerrainsController::delete_terrain_project(const HttpRequestPtr &req,
     std::function<void (const HttpResponsePtr &)> &&callback,
     std::string userName, std::string projName)
{
    int ret_code, uuid;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            ret_code = __terrains_service->delete_terrain_project(userName, projName);
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

void api::v1::TerrainsController::get_rating_terrain_project(const HttpRequestPtr &req,
               std::function<void (const HttpResponsePtr &)> &&callback,
               std::string projName)
{
    int ret_code, uuid;
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
            ret_code = __terrains_service->get_terrain_project_rating(projName, rating);
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
               std::string projName)
{
    int ret_code, uuid;
    Json::Value jsonBody;
    std::string token, rating, userName;
    drogon::HttpResponsePtr resp;
    json json_get;

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            json_get = json::parse(req->bodyData());
            userName = json_get["userName"];
            std::cerr << "userName: " << userName << "\n";
            ret_code = __terrains_service->set_terrain_project_rating(projName, userName);
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
    std::string filename = "../images/fee.png";

    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBodyout);
        }
        else{
            jsonBodyIn = req->getJsonObject();
            scene_info = __handle_json_body(jsonBodyIn);
            ret_code = __terrains_service->get_render_png_image(scene_info.first, scene_info.second);
            resp = form_http_response(ret_code, filename);
        }
        callback(resp);
    }
    catch (std::exception &e) {
        std::cerr << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBodyout);
        callback(resp);
    }
}

void api::v1::TerrainsController::add_project_for_rating(
        const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,
        std::string userName, std::string projName)
{
    int ret_code, uuid;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;

    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            ret_code = __terrains_service->add_project_for_rating(userName, projName);
            resp = form_http_response(ret_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e){
        std::cout << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::get_all_rating_projects(
        const HttpRequestPtr &req,
        std::function<void (const HttpResponsePtr &)> &&callback,
        std::string page)
{
    int ret_code, uuid;
    Json::Value jsonBody;
    std::string token;
    drogon::HttpResponsePtr resp;
    std::vector<servTerrainProject_t> terProjects;
    try
    {
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            ret_code = __terrains_service->get_all_rating_projects(page, terProjects);
            jsonBody = form_json_response(terProjects);
            resp = form_http_response(ret_code, jsonBody);
        }
        callback(resp);
    }
    catch (std::exception &e){
        std::cout << e.what();
        ret_code = BAD_REQUEST;;
        resp = form_http_response(ret_code, jsonBody);
        callback(resp);
    }
}

void api::v1::TerrainsController::find_rating_project(
        const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback,
        std::string projName)
{
    int ret_code, uuid;
    drogon::HttpResponsePtr resp;
    servTerrainProject_t project;
    std::string token;

    Json::Value jsonBody;
    try{
        token = req.get()->getHeader("Authorization");
        uuid = std::stoi(req.get()->getHeader("uuid"));
        ret_code = __sessions.check_usr_authorization(token, uuid);
        if (ret_code != SUCCESS){
            resp = form_http_response(ret_code, jsonBody);
        }
        else{
            ret_code = __terrains_service->find_rating_project(projName, project);
            jsonBody = form_json_response(project);
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


std::pair<dbTerrain_t, light_t>
    api::v1::TerrainsController::__handle_json_body(std::shared_ptr<Json::Value> jsonBodyIn)
{
    dbTerrain_t terrain;
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

servTerrain_t api::v1::TerrainsController::__handle_json_Body(std::shared_ptr<Json::Value> jsonBodyIn)
{
    servTerrain_t terrain;

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

    return terrain;
}
