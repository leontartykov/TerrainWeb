#include "postgres.h"

Postgres::Postgres(){
    __connect_psql_to_db();
    __users = std::make_unique<UserPostgres>(__connection);
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

int Postgres::do_action_users(const users_action &action, users_t &user)
{
    int http_response_code = 0;

    switch(action){
        case add:
            __users.get()->add(user);
            break;
        case get:
            http_response_code = __users.get()->get(user.id, user);
            break;
        case update:
            __users.get()->update(user.id, user);
            break;
        case delete_user:
            __users.get()->delete_user(user.id);
            break;
        case block:
            __users.get()->block(user.id);
            break;
        case unlock:
            __users.get()->unlock(user.id);
            break;
    }

    return http_response_code;
}

int Postgres::get_count_users(){
    return __users.get()->get_count_users();
}

void Postgres::set_psql_connection(std::shared_ptr<pqxx::connection> &connection){
    __connection = connection;
}
