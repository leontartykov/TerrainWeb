#include "postgres.h"

Postgres::Postgres(){
    __connect_psql_to_db();
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
        __users.set_psql_connection(__connection);
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        return -2;
    }

    return 0;
}

std::pair<int, users_t> Postgres::do_action_users(const users_action &action, users_t &user)
{
    users_t get_user;
    int return_code_error;
    std::cout << "action: " << action << "\n";
    switch(action){
        case add:
            __users.add(user);
            break;
        case get:
            get_user = __users.get(user.id);
            return_code_error = 200;
            break;
        case update:
            __users.update_login(user.id, user.login);
            break;
        case delete_user:
            __users.delete_user(user.id);
            break;
        case block:
            __users.block(user.id);
            break;
        case unlock:
            __users.unlock(user.id);
            break;
    }

    return std::make_pair(return_code_error, get_user);
}

void Postgres::set_psql_connection(std::shared_ptr<pqxx::connection> &connection){
    __connection = connection;
}
