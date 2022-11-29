#include "json_former.hpp"

json form_json_response(std::vector<dbTerrainProject_t> &ter_projs)
{
    json json_ret, jsonObjects;
    int count_ter_projs;

    jsonObjects = json::array();
    count_ter_projs = ter_projs.size();
    for(int i = 0; i < count_ter_projs; ++i)
    {
        json_ret["id"] = ter_projs[i].id;
        json_ret["name"] = ter_projs[i].name;
        json_ret["last_edited"] = ter_projs[i].last_edit;
        jsonObjects.push_back(json_ret);
    }
    json_ret = jsonObjects;

    return json_ret;
}

json form_json_response(dbTerrainProject_t &ter_proj)
{
    json json_ret;
    json_ret["rotate"]["angle_x"] = ter_proj.terrain.rotate_angles.angle_x;
    json_ret["rotate"]["angle_y"] = ter_proj.terrain.rotate_angles.angle_y;
    json_ret["rotate"]["angle_z"] = ter_proj.terrain.rotate_angles.angle_z;

    json_ret["config"]["octaves"] = ter_proj.terrain.meta_config.octaves;
    json_ret["config"]["gain"] = ter_proj.terrain.meta_config.gain;
    json_ret["config"]["lacunarity"] = ter_proj.terrain.meta_config.lacunarity;
    json_ret["config"]["seed"] = ter_proj.terrain.meta_config.seed;
    json_ret["config"]["frequency"] = ter_proj.terrain.meta_config.frequency;

    json_ret["scale"] = ter_proj.terrain.scale;

    json_ret["size"]["width"] = ter_proj.terrain.width;
    json_ret["size"]["height"] = ter_proj.terrain.height;

    return json_ret;
}

json form_json_response(dbUsers_t &user)
{
    json json_ret;
    json_ret["login"] = user.login;
    json_ret["perm_level"] = user.perm_level;

    return json_ret;
}

json form_json_response(std::string token, int &user_id)
{
    json json_ret;
    json_ret["access_token"] = token;
    json_ret["id"] = user_id;

    return json_ret;
}
