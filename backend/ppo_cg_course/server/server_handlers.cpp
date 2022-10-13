#include "async_con.h"

bool tcp_connection::__handle_post_request()
{
    if (!__request.payload_size()){
        return false;
    }

    std::string url = __request.target().data();
    std::size_t target_url = url.find_last_of("/\\");
    std::cout << "target_url: " << target_url << "\n";

    std::cout << " file: " << url.substr(target_url+1) << '\n';

    std::cout << "Content-Length: " << (__request.has_content_length()? "explicit ":"implicit ") << "\n";

    return true;
}

bool tcp_connection::__handle_get_request()
{
    std::string url, endpoint, category;
    std::size_t target_url;
    int id;
    users_t user;

    url = __request.target().data();
    target_url = url.find_last_of("/\\");
    endpoint = url.substr((url.substr(0, target_url).find_last_of("/\\"))+1, target_url);
    id = std::stoi(endpoint.substr(endpoint.find_last_of("/\\")+1).c_str());
    category = endpoint.substr(0, endpoint.find_last_of("/\\"));

    std::cout << "target_url: " << target_url << "\n";
    std::cout << "endpoint: " << endpoint << "\n";
    std::cout << "id: " << id << "\n";
    std::cout << "category: " << category << '\n';

    user.id = id;

    if (category == "users"){
        std::pair<int, users_t> get_result = __postgres.do_action_users(users_action::get, user);
        int code_error = get_result.first;
        users_t get_user = get_result.second;
        std::cout << "RESULTS: ";
        std::cout << get_user.id << " " << get_user.login << " " << get_user.password << "\n";
    }

    return true;
}
