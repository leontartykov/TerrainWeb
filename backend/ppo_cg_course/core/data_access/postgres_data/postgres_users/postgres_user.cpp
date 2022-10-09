#include "postgres_user.h"

users_t UserPostgres::get_by_id(int id)
{
    users_t res_user;
    pqxx::work worker(*__conn_psql);
    std::string query = "SELECT * FROM terrain_project.users.passwords WHERE id = '" + \
                         std::to_string(id) + "';";

    pqxx::result response = worker.exec(query);

    res_user.login = response[0][1].c_str();
    res_user.password = response[0][2].c_str();
    res_user.is_blocked = response[0][3].c_str();
    res_user.is_deleted = response[0][4].c_str();

    return res_user;
}

int UserPostgres::add(users_t &user)
{
    if (!__conn_psql){
        std::cout << "error: Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (!__is_user_empty(user)){
        std::cout << "О пользователе нет данных.\n";
        return -2;
    }
    try{
        pqxx::work worker(*__conn_psql);

        std::string query = "INSERT terrain_project.users.passwords values ('" + \
                            user.login + "', '" + user.password + "', false, " + "false)";
        worker.exec(query);
        worker.commit();
        std::cout << "пользователь был добавлен успешно.\n";
    }
    catch (std::exception const &e){
        std::cout << e.what() << '\n';
        return -3;
    }

    std::cout << "Добавление в psql произошло успешно.\n";

    return 0;
}

int UserPostgres::delete_user(int id)
{
    if (!__conn_psql){
        std::cout << "Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (!id){
        std::cout << "О пользователе нет данных (ID).\n";
        return -2;
    }

    try{
        users_t del_user;
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.passwords SET delete = true WHERE id = '" + \
                            std::to_string(id) + "';";
        worker.exec(query);
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int UserPostgres::update_login(int id, std::string new_login)
{
    try{
        users_t del_user;
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.passwords SET login = " + \
                            new_login + " WHERE id = '" + std::to_string(id) + "';";
        worker.exec(query);
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int UserPostgres::block(std::string login)
{
    if (login.empty()){
        std::cout << "О пользователе нет данных.\n";
        return -1;
    }

    try{
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.passwords SET blocked = true WHERE login LIKE '%" + login + "';";
        worker.exec(query);
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int UserPostgres::unlock(std::string login)
{
    try{
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.passwords SET lock = false WHERE login LIKE '%" + login + "';"
        worker.exec(query);
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

bool UserPostgres::__is_user_empty(users_t &user){
    if (user.password.empty() && user.login.empty()){
        return true;
    }

    return false;
}

void UserPostgres::__disconnect_db()
{
    if (__conn_psql){
        __conn_psql->disconnect();
        __conn_psql = nullptr;
        std::cout << "Отключение от psql проведено успешно." << std::endl;
    }
    else{
        std::cout << "Не было подключения к БД psql." << std::endl;
    }
}

void UserPostgres::set_psql_connection(std::shared_ptr<pqxx::connection> &conn_psql){
    __conn_psql = conn_psql;
}
