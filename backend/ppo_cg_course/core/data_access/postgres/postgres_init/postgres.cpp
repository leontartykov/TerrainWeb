#include "postgres.h"

Postgres::Postgres(){
    __connect_psql_to_db();
    __users = std::make_unique<UserPostgres>(__connection);
    __terrains = std::make_unique<TerrainProjectsPostgres>(__connection);
}

int Postgres::__connect_psql_to_db()
{
    config_t config_data;
    std::string options;

    if (__connection){
        std::cout << "Уже есть подключение к БД.\n";
        return 0;
    }

    try
    {
        config_data = __config.read_config_file_postgres();
        options = __config.form_options(config_data);
        __connection = std::shared_ptr<pqxx::connection>(new pqxx::connection(options));
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        return -2;
    }

    return 0;
}

int Postgres::get_count_users(){
    return __users.get()->get_count_users();
}

int Postgres::get_count_terrains(){
    return __terrains.get()->get_count_terrain_projects();
}

void Postgres::set_psql_connection(std::shared_ptr<pqxx::connection> &connection){
    __connection = connection;
}

int Postgres::do_action_users(const users_action &action, users_t &user)
{
    int http_response_code = 0;

    switch(action){
        case add_u:
            http_response_code = __users.get()->add(user);
            break;
        case get_u:
            http_response_code = __users.get()->get(user.id, user);
            break;
        case update_u:
            __users.get()->update(user.id, user);
            break;
        case delete_u:
            __users.get()->delete_user(user.id);
            break;
        case block_u:
            __users.get()->block(user.id);
            break;
        case unlock_u:
            __users.get()->unlock(user.id);
            break;
    }

    return http_response_code;
}

int Postgres::do_action_terrains(const terrains_action &action, terrain_project_t &ter_proj, int &user_id)
{
    int http_response_code = 0;

    if (user_id > get_count_users()){
        http_response_code = 404;
    }
    else{
        switch(action)
        {
            case add_t:
                http_response_code = __terrains.get()->add_new_terrain_project(ter_proj, user_id);
                break;
            case get_tpl:
                std::cout << "Нет функционала.\n";
                break;
            case get_t:
                http_response_code = __terrains.get()->get_terrain_project(ter_proj, user_id);
                break;
            case update_t:
                std::cout << "Нет функционала.\n";
                break;
            case delete_t:
                std::cout << "Нет функционала.\n";
                break;
            default:
                std::cout << "Неизвестная команда.\n";
        }
    }

    std::cout << "terrain_http_error: " << http_response_code << "\n";

    return http_response_code;
}
