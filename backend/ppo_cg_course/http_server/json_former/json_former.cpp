#include "http_server/json_former/json_former.hpp"

Json::Value form_json_response(dbUsers_t &user)
{
    Json::Value json_ret;
    json_ret["login"] = user.login;
    json_ret["perm_level"] = user.perm_level;
    /*Json::Value json;
    json["path"] = "json";
    json["name"] = "json test";
    Json::Value array;
    for (int i = 0; i < 5; ++i)
    {
        Json::Value user;
        user["id"] = i;
        user["name"] = "none";
        user["c_name"] = "张三";
        array.append(user);
    }
    json["rows"] = array;*/


    return json_ret;
}

Json::Value form_json_response(std::vector<servTerrainProject_t> &ter_projs)
{
    int count_ter_projs;
    Json::Value jsonObj, jsonObjects;

    count_ter_projs = ter_projs.size();
    for(int i = 0; i < count_ter_projs; ++i)
    {
        jsonObj["id"] = ter_projs[i].id;
        jsonObj["name"] = ter_projs[i].name;
        jsonObj["last_edited"] = ter_projs[i].last_edit;
        jsonObjects.append(jsonObj);
    }

    return jsonObjects;
}

Json::Value form_json_response(const servTerrain_t &terrain)
{
    Json::Value json_ret;
    json_ret["rotate"]["angle_x"] = terrain.rotate_angles.angle_x;
    json_ret["rotate"]["angle_y"] = terrain.rotate_angles.angle_y;
    json_ret["rotate"]["angle_z"] = terrain.rotate_angles.angle_z;

    json_ret["config"]["octaves"] = terrain.meta_config.octaves;
    json_ret["config"]["gain"] = terrain.meta_config.gain;
    json_ret["config"]["lacunarity"] = terrain.meta_config.lacunarity;
    json_ret["config"]["seed"] = terrain.meta_config.seed;
    json_ret["config"]["frequency"] = terrain.meta_config.frequency;

    json_ret["scale"] = terrain.scale;

    json_ret["size"]["width"] = terrain.width;
    json_ret["size"]["height"] = terrain.height;

    return json_ret;
}

Json::Value form_json_response(std::string &token, int &user_id)
{
    Json::Value json_ret;
    json_ret["access_token"] = token;
    json_ret["uuid"] = user_id;

    return json_ret;
}

Json::Value form_json_response(double &terProjRating)
{
    Json::Value json_ret;
    json_ret["rating"] = terProjRating;
    return json_ret;
}
