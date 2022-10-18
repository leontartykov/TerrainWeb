#include "async_con.h"
#include <boost/property_tree/json_parser.hpp>

int tcp_connection::__define_user_id()
{
    std::size_t target_url;
    std::string url, cut_url;

    url = __request.target().data();
    target_url = url.find_last_of("/\\");
    url = url.substr(0, target_url);

    target_url = url.find_last_of("/\\");
    url = url.substr(0, target_url);

    target_url = url.find_last_of("/\\");
    url = url.substr(target_url+1);

    std::cout << "user_id: " << url << "\n";

    return std::stoi(url);
}

void tcp_connection::__define_category(std::string &category)
{
    std::size_t target_url;
    std::string url;

    url = __request.target().data();
    target_url = url.find_last_of("/\\");

    category = url.substr(target_url + 1);
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}


bool tcp_connection::__define_target_url(int &id, std::string &category)
{
    std::string url, endpoint, id_string;
    std::size_t target_url;

    /*if (!__request.payload_size()){
        return false;
    }*/

    std::cout << __request.target().data() << "\n";
    url = __request.target().data();
    std::cout << "url: " << url << "\n";

    target_url = url.find_last_of("/\\");
    std::cout << "target_url: " << target_url << "\n";

    endpoint = url.substr((url.substr(0, target_url).find_last_of("/\\"))+1, target_url);

    std::cout << "endpoint: " << endpoint << "\n";

    id_string = endpoint.substr(endpoint.find_last_of("/\\")+1).c_str();
    std::cout << "id_string: " << id_string << "\n";

    if (!id_string.empty()){
        id = std::stoi(id_string);
    }

    category = endpoint.substr(0, endpoint.find_last_of("/\\"));

    return true;
}

bool tcp_connection::__handle_post_request(int &http_response_code)
{
    users_t user;
    json j_complete;
    std::string category;
    terrain_project_t ter_proj;
    int user_id;

    if (!__request.payload_size()){
        return false;
    }

    __define_category(category);
    std::cout << "category: " << category << "\n";
    j_complete = json::parse(__request.body().c_str());
    std::cout << std::setw(4) << j_complete << std::endl;


    if (category == "users"){
        user.id = __postgres.get_count_users();
        user.login = j_complete["login"];
        user.password = j_complete["password"];
        http_response_code = __postgres.do_action_users(users_action::add_u, user);
    }
    else if (category == "terrains"){
        user_id = __define_user_id();
        ter_proj.id = __postgres.get_count_terrains() + 1;
        ter_proj.name = j_complete["name"];
        http_response_code = __postgres.do_action_terrains(terrains_action::add_t, ter_proj, user_id);
    }

    return true;
}

bool tcp_connection::__handle_put_request(int &http_response_code)
{
    users_t user;
    json j_complete;
    std::string category;

    if (!__request.payload_size()){
        return false;
    }

    __define_category(category);
    std::cout << "category: " << category << "\n";
    j_complete = json::parse(__request.body().c_str());
    std::cout << std::setw(4) << j_complete << std::endl;


    if (category == "users"){
        user.id = __postgres.get_count_users();
        user.login = j_complete["login"];
        http_response_code = __postgres.do_action_users(users_action::update_u, user);
    }

    return true;
}

bool tcp_connection::__handle_patch_request(int &http_response_code)
{
    users_t user;
    json j_complete;
    std::string category;
    int id;

    if (!__request.payload_size()){
        return false;
    }

    __define_target_url(id, category);
    std::cout << "id: " << id << "\n";
    std::cout << "category: " << category << "\n";

    j_complete = json::parse(__request.body().c_str());
    std::cout << std::setw(4) << j_complete << std::endl;


    if (category == "users"){
        user.id = id;
        user.login = j_complete["login"];
        http_response_code = __postgres.do_action_users(users_action::update_u, user);
    }

    return true;
}

std::string tcp_connection::__handle_get_request(int &http_response_code)
{
    int id = 0, user_id;
    std::string category;
    users_t user;
    terrain_project_t ter_proj;
    json j_return;
    ptree pt, angles_array, meta_config_array, size_array;

    __define_category(category);
    if (is_number(category)){
        __define_target_url(id, category);
        std::cout << "id: " << id << "\n";
    }

    std::cout << "category: " << category << '\n';

    if (category == "users"){
        user.id = id;
        http_response_code = __postgres.do_action_users(users_action::get_u, user);
        if (http_response_code == 200)
        {
            // form json file format
            j_return["login"] = user.login;
            j_return["perm_level"] = user.perm_level;
        }
    }
    if (category == "terrains"){
        user_id = __define_user_id();
        ter_proj.id = id;
        http_response_code = __postgres.do_action_terrains(terrains_action::get_t, ter_proj, user_id);

        if (http_response_code == 200 || http_response_code == 0)
        {
            j_return["size"]["width"] = ter_proj.terrain.width;
            j_return["size"]["height"] = ter_proj.terrain.height;

            j_return["scale"] = ter_proj.terrain.scale;

            j_return["config"]["octaves"] = ter_proj.terrain.meta_config.octaves;
            j_return["config"]["gain"] = ter_proj.terrain.meta_config.gain;
            j_return["config"]["lacunarity"] = ter_proj.terrain.meta_config.lacunarity;
            j_return["config"]["seed"] = ter_proj.terrain.meta_config.seed;
            j_return["config"]["frequency"] = ter_proj.terrain.meta_config.frequency;

            j_return["rotate"]["angle_x"] = ter_proj.terrain.rotate_angles.angle_x;
            j_return["rotate"]["angle_y"] = ter_proj.terrain.rotate_angles.angle_y;
            j_return["rotate"]["angle_z"] = ter_proj.terrain.rotate_angles.angle_z;
        }
    }

    return j_return.dump(4);
}
