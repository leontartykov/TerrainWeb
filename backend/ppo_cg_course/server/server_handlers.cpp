#include "async_con.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

void tcp_connection::__define_category(std::string &category)
{
    std::size_t target_url;
    std::string url;

    url = __request.target().data();
    target_url = url.find_last_of("/\\");

    category = url.substr(target_url + 1);
}

bool tcp_connection::__define_target_url(int &id, std::string &category)
{
    std::string url, endpoint;
    std::size_t target_url;

    if (!__request.payload_size()){
        return false;
    }

    url = __request.target().data();
    target_url = url.find_last_of("/\\");
    endpoint = url.substr((url.substr(0, target_url).find_last_of("/\\"))+1, target_url);

    id = std::stoi(endpoint.substr(endpoint.find_last_of("/\\")+1).c_str());
    category = endpoint.substr(0, endpoint.find_last_of("/\\"));

    return true;
}

bool tcp_connection::__handle_post_request(int &http_response_code)
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
        user.password = j_complete["password"];
        http_response_code = __postgres.do_action_users(users_action::add, user);
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
        http_response_code = __postgres.do_action_users(users_action::update, user);
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
        http_response_code = __postgres.do_action_users(users_action::update, user);
    }

    return true;
}

std::stringstream tcp_connection::__handle_get_request(int &http_response_code)
{
    int id;
    std::string category;
    users_t user;
    std::stringstream ss;
    boost::property_tree::ptree pt;

    __define_target_url(id, category);

    std::cout << "id: " << id << "\n";
    std::cout << "category: " << category << '\n';
    std::cout << __request.base() << "\n";

    user.id = id;

    if (category == "users"){
        http_response_code = __postgres.do_action_users(users_action::get, user);
        std::cout << "http_response_code: " << http_response_code << "\n";
        if (http_response_code == 200){
            // form json file format
            pt.put("login", user.login);
            pt.put("perm_level", user.perm_level);

            boost::property_tree::json_parser::write_json(ss, pt);

            std::cout << ss.str() << std::endl;
        }
    }

    return ss;
}
