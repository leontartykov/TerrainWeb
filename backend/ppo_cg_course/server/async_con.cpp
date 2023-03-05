#include <boost/beast/version.hpp>
#include <chrono>
#include <ctime>   // localtime
#include <sstream> // stringstream
#include <iomanip> // put_time

#include "async_con.h"
#include "./server/server_codes.h"

tcp_connection::tcp_connection(io_service &io_context): __socket(io_context){}

tcp_connection::pointer tcp_connection::create(io_service &io_context){
    return pointer(new tcp_connection(io_context));
}

tcp::socket &tcp_connection::socket(){
    return __socket;
}

///Entry point to handle requests
void tcp_connection::start(){
    handle_request();
}

void tcp_connection::handle_write(http::response<http::buffer_body> &response){
    http::write(__socket, response);
}

void tcp_connection::handle_read(){
    streambuf buf;
    http::read(__socket, buf, __request);
}

http::response<http::buffer_body> tcp_connection::__form_htpp_response_code(int &http_response_code)
{
    http::response<http::buffer_body> response;
    if (http_response_code == 0 || http_response_code == SERV_SUCCESS){
        response.result(http::status::ok);
    }
    else if (http_response_code == SERV_SUCCESS_CREATED){
        response.result(http::status::created);
    }
    else if (http_response_code == SERV_BAD_REQUEST){
        response.result(http::status::bad_request);
    }
    else if (http_response_code == SERV_FORBIDDEN){
        response.result(http::status::forbidden);
    }
    else if (http_response_code == SERV_NOT_FOUND){
        response.result(http::status::not_found);
    }

    response.version(__request.version());
    response.set(http::field::server, "Terrain Server");
    response.set("Access-Control-Allow-Methods", "GET, DELETE, PUT, POST, PATCH");
    response.set("Access-Control-Allow-Origin", "*");
    response.set("Access-Control-Allow-Headers", "Accept, Authorization, Cache-Control, \
                 Content-Type, DNT, Id, If-Modified-Since, Keep-Alive, Origin, User-Agent, X-Requested-With");
    response.keep_alive(__request.keep_alive());

    if (!__response_buffer.empty())
    {
        response.set(beast::http::field::content_type, "application/json");
        response.content_length(strlen(__response_buffer.c_str()));
        response.body().data = (void *)__response_buffer.c_str();
        response.body().size = strlen(__response_buffer.c_str());
        response.body().more = false;
    }
    else{
        response.content_length(0);
        response.body().more = false;
    }

    return response;
}

///Form log info (access or error)
/// Time | port | protocol |  method | request url | response code | destination
void tcp_connection::__form_log_info(int &http_response_code)
{
    std::string log_info {};
    std::stringstream ss;
    unsigned version;

    //form time
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    log_info += ss.str() + " ";

    version = __request.version();

    log_info += std::string(__request.base()["Host"]) + " HTTP/" + std::to_string(version / 10) + \
                "." + std::to_string(version % 10) + " " + \
                std::string(__request.method_string()) + " " + __url_path + \
                " ";

    __logs_access.write_log(log_info);
}

///Parse all elements in url path
void tcp_connection::__form_url_path_elems()
{
    std::string url_path;
    int count = 10, target_path, i;
    bool end_parse = false;
    url_path = __request.target().to_string();

    //this url is for log
    __url_path = url_path;

    __url_path_elems.resize(count);

    for (int i = 0; i < 2; ++i){
        target_path = url_path.find_first_of("/\\");
        url_path = url_path.substr(target_path+1);
    }

    for (i = 0; !end_parse; ++i){
        target_path = url_path.find_last_of("/\\");
        if (target_path == -1){
            end_parse = true;
        }

        __url_path_elems[i] = url_path.substr(target_path+1);
        url_path = url_path.substr(0, target_path);
    }

    count = i;
    __url_path_elems.resize(count);
}

///Check user authorization
bool tcp_connection::__check_authorization(){
    std::string token = "";
    int user_id = -1;
    bool success = true;
    try
    {
        token = __request.base()["Authorization"].to_string();
        user_id = std::stoi(__request.base()["Id"].to_string());
        success = __sessions.check_access_token(user_id, token);
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        success = false;
    }

    return success;
}

///Handle http methods
bool tcp_connection::handle_request()
{
    int http_response_code = SERV_SUCCESS;
    http::verb method;
    http::response<http::buffer_body> response;

    handle_read();
    method = __request.method();
    __form_url_path_elems();

    if (method != http::verb::options && __define_category() == "login"){
        __response_buffer = __handle_post_request(http_response_code);
    }
    else if (method != http::verb::options && !__check_authorization()){
        http_response_code = SERV_FORBIDDEN;
    }
    else
    {
          switch (method)
          {
            case http::verb::unknown:
                std::cout << "Неизвестный запрос.\n";
                break;
            case http::verb::get:
                __response_buffer = __handle_get_request(http_response_code);
                break;
            case http::verb::post:
                __response_buffer = __handle_post_request(http_response_code);
                break;
            case http::verb::put:
                __handle_put_request(http_response_code);
                std::cout << "пока нет функционала для этого запроса PUT.\n";
                break;
            case http::verb::patch:
                __handle_patch_request(http_response_code);
                break;
            case http::verb::delete_:
                __handle_delete_request(http_response_code);
                break;
            case http::verb::head:
                std::cout << "пока нет функционала для этого запроса HEAD.\n";
                break;
            case http::verb::options:
                break;
            default:
                std::cout << "пока нет функционала для этого запроса.\n";
                break;
        }
    }

    response = __form_htpp_response_code(http_response_code);
    __form_log_info(http_response_code);
    handle_write(response);

    return true;
}
