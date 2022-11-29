#include <boost/property_tree/json_parser.hpp>
#include <nlohmann/json.hpp>

#include "./server/async_con.h"
#include "./server/server_codes.h"
#include "./server/json_former/json_former.hpp"
#include "./server/jwt/jwt.hpp"

using json = nlohmann::json;

///Define info id:
/// if "info" is terrain -- define terrain id
/// if "info" is user -- define user id
int tcp_connection::__define_info_id(std::string info){
    int info_id = -1;
    int url_elems_count = __url_path_elems.size();
    bool find_flag = false;
    for (int i = 0; !find_flag && i < url_elems_count; ++i)
    {
        if (__url_path_elems[i] == info){
            find_flag = true;
            info_id = std::stoi(__url_path_elems[i-1]);
        }
    }

    return info_id;
}

///Define if string is number
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

///Define url category
std::string tcp_connection::__define_category(){
    if (is_number(__url_path_elems[0])){
        return __url_path_elems[1];
    }

    return __url_path_elems[0];
}

///Post http method handler
std::string tcp_connection::__handle_post_request(int &http_response_code)
{
    dbUsers_t user;
    json j_complete, json_ret;
    std::string category;
    dbTerrainProject_t ter_proj;
    int user_id;
    std::string msg, access_token;

    if (!__request.payload_size()){
        return "false";
    }

    category = __define_category();
    j_complete = json::parse(__request.body().c_str());

    if (category == "login"){
        user.login = j_complete["login"];
        user.password = j_complete["password"];
        if (__postgres.check_validation(user)){
            http_response_code = SERV_SUCCESS;
            JWTUser jwt_user;
            access_token = jwt_user.create_token();
            __sessions.add(user.id, access_token);
            json_ret = form_json_response(access_token, user.id);
        }
        else{
            http_response_code = SERV_FORBIDDEN;
        }
    }
    else if (category == "users"){
        user.id = __postgres.get_count_users();
        user.login = j_complete["login"];
        user.password = j_complete["password"];
        user.perm_level = j_complete["perm_level"];
        http_response_code = __postgres.do_action_users(users_action::add_u, user);
    }
    else if (category == "terrains"){
        user_id = __define_info_id("users");
        ter_proj.id = __postgres.get_count_terrains() + 1;
        std::cout << "user_id: " << user_id << " terrain_id: " << ter_proj.id << "\n";
        ter_proj.name = j_complete["name"];
        http_response_code = __postgres.do_action_terrains(terrains_action::add_t, ter_proj, user_id);
    }

    return json_ret.dump(4);
}

///Put http method handler
bool tcp_connection::__handle_put_request(int &http_response_code)
{
    users_t user;
    json j_complete;
    std::string category;

    if (!__request.payload_size()){
        return false;
    }

    category = __define_category();
    j_complete = json::parse(__request.body().c_str());


    if (category == "users"){
        user.id = __postgres.get_count_users();
        user.login = j_complete["login"];
        http_response_code = __postgres.do_action_users(users_action::update_u, user);
    }

    return true;
}

///Patch http method handler
bool tcp_connection::__handle_patch_request(int &http_response_code)
{
    users_t user;
    json j_complete;
    std::string category;

    if (!__request.payload_size()){
        return false;
    }

    category = __define_category();
    j_complete = json::parse(__request.body().c_str());

    if (category == "users"){
        user.id = __define_info_id("users");
        user.login = j_complete["login"];
        http_response_code = __postgres.do_action_users(users_action::update_u, user);
    }

    return true;
}

///Delete http method handler
bool tcp_connection::__handle_delete_request(int &http_response_code)
{
    users_t user;
    json j_complete;
    std::string category;
    terrain_project_t ter_proj;
    int user_id;

    if (!__request.payload_size()){
        return false;
    }

    category = __define_category();

    if (category == "users"){
        user.id = __define_info_id("users");
        http_response_code = __postgres.do_action_users(users_action::delete_u, user);
    }
    else if (category == "terrains"){
        user_id = __define_info_id("users");
        ter_proj.id = __define_info_id("terrains");
        http_response_code = __postgres.do_action_terrains(terrains_action::delete_t, ter_proj, user_id);
    }

    return true;
}

///Get http method handler
std::string tcp_connection::__handle_get_request(int &http_response_code)
{
    int _id = 0, user_id;
    std::string category;
    users_t user;
    terrain_project_t ter_proj;
    json json_ret;
    ptree pt, angles_array, meta_config_array, size_array;

    category = __define_category();

    if (category == "users"){
        user.id = __define_info_id("users");
        http_response_code = __postgres.do_action_users(users_action::get_u, user);
        if (http_response_code == SERV_SUCCESS){
            json_ret = form_json_response(user);
        }
    }
    else if (category == "terrains")
    {
        user_id = __define_info_id("users");
        if (__url_path_elems.size() == 6)
        {
            ter_proj.id = _id;
            http_response_code = __postgres.do_action_terrains(terrains_action::get_t, ter_proj, user_id);

            if (http_response_code == SERV_SUCCESS || http_response_code == SERV_OK){
                json_ret = form_json_response(ter_proj);
            }
        }
        else if (__url_path_elems.size() == 5)
        {
            std::pair<int, std::vector<terrain_project_t>>
                    result = __postgres.do_action_terrain_projects(ter_projs_action::get_tpl, user_id);
            http_response_code = result.first;
            if (http_response_code == SERV_SUCCESS || http_response_code == SERV_OK){
                json_ret = form_json_response(result.second);
            }
        }
    }
    return json_ret.dump(4);
}
