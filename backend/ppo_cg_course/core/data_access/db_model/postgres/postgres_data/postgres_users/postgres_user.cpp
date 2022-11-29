#include "postgres_user.h"
#include <QDebug>

UserPostgres::UserPostgres(std::shared_ptr<pqxx::connection> &conn_psql){
    __conn_psql = conn_psql;
    __define_count_users();
}

int UserPostgres::get(int &id, dbUsers_t &user)
{
    int http_response_code = 200;
    if (!id){
        http_response_code = 400;
    }
    else if (id >= __count_users){
        http_response_code = 404;
    }
    else{
        pqxx::work worker(*__conn_psql);
        std::string query = "SELECT * FROM terrain_project.users.info WHERE id = '" + \
                             std::to_string(id) + "';";

        pqxx::result response = worker.exec(query);

        user.id = std::stoi(response[0][0].c_str());
        user.login = response[0][1].c_str();
        user.password = response[0][2].c_str();
        user.perm_level = std::stoi(response[0][3].c_str());
        user.is_blocked = response[0][4].c_str();
        user.is_deleted = response[0][5].c_str();
    }

    return http_response_code;
}

int UserPostgres::get_count_users(){
    return __count_users;
}

int UserPostgres::add(dbUsers_t &user)
{
    std::string query;
    pqxx::result response;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return -1;
    }
    else if (__is_user_empty(user)){
        std::cout << "О пользователе нет данных.\n";
        return -2;
    }
    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT * from terrain_project.users.info where login like '%" \
                 + user.login + "';";
        response = worker.exec(query);

        if (!response.empty()){
            query = "UPDATE terrain_project.users.info SET deleted = false \
                     WHERE login like '%" + user.login + "';";
        }
        else
        {
            __count_users++;

            query = "INSERT INTO terrain_project.users.info values (" + \
                                std::to_string(user.id) + ", '" +
                                user.login + "', '" + user.password + "', " + std::to_string(user.perm_level) +
                                ", false, " + "false)";
        }
        worker.exec(query);
        worker.commit();
        std::cout << "Пользователь был добавлен успешно.\n";
    }
    catch (std::exception const &e){
        std::cout << e.what() << '\n';
        return -3;
    }

    std::cout << "\nДобавление в psql произошло успешно.\n";

    return 0;
}

int UserPostgres::delete_user(int &id)
{
    int success = 0;
    if (!__conn_psql){
        std::cout << "Нет подключения к БД." << std::endl;
        success = -1;
    }
    else if (!id){
        std::cout << "О пользователе нет данных (ID).\n";
        success = -2;
    }

    try{
        dbUsers_t del_user;
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.info SET deleted = true WHERE id = '" + \
                            std::to_string(id) + "';";
        pqxx::result result = worker.exec(query);

        worker.commit();
        std::cout << "\nУдаление пользователя выполнено успешно.\n";
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return success;
}

int UserPostgres::update(int &id, dbUsers_t &user)
{
    int response_code = 0;
    try{
        dbUsers_t del_user;
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.info SET login = '" + \
                            user.login + "' WHERE id = '" + std::to_string(id) + "';";
        worker.exec(query);
        worker.commit();
        std::cout << "\nЛогин обновлен успешно.\n";
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        response_code = -3;
    }

    return response_code;
}

int UserPostgres::block(int &id)
{
    if (!id){
        std::cout << "О пользователе нет данных.\n";
        return -1;
    }

    try{
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.info SET blocked = true WHERE id = " \
                             + std::to_string(id) + ";";
        worker.exec(query);
        worker.commit();

        std::cout << "\nБлокировка пользователя выполнена успешно.\n";
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int UserPostgres::unlock(int &id)
{
    if (!id){
        std::cout << "О пользователе нет данных.\n";
        return -1;
    }

    try{
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.info SET blocked = false WHERE id = " \
                            + std::to_string(id) + ";";
        worker.exec(query);
        worker.commit();
        std::cout << "\nРазблокировка пользователя выполнена успешно.\n";
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

bool UserPostgres::check_validation(dbUsers_t &user)
{
    std::string query;
    pqxx::result response;
    bool success = true;
    user.id = -1;

    if (user.login.empty() || user.password.empty()){
        return false;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT info.id, info.blocked, info.deleted " \
                "FROM terrain_project.users.info as info " \
                "WHERE info.login = '" + user.login + "' AND info.password = '" + user.password + "';";
        response = worker.exec(query);
        if (response.empty()){
            success = false;
        }
        else{
            user.id = response[0][0].as<int>();
            user.is_blocked = response[0][1].c_str();
            user.is_deleted = response[0][2].c_str();
        }
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -2;
    }

    return success;
}

bool UserPostgres::__is_user_empty(dbUsers_t &user){
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
        std::cout << "Отключение от psql проведено успешно.\n";
    }
    else{
        std::cout << "Не было подключения к БД psql.\n";
    }
}

void UserPostgres::set_psql_connection(std::shared_ptr<pqxx::connection> &conn_psql){
    __conn_psql = conn_psql;
}

void UserPostgres::__define_count_users()
{
    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return;
    }

    try{
        pqxx::work worker(*__conn_psql);
        std::string query = "SELECT COUNT(*) FROM terrain_project.users.info";
        pqxx::result response = worker.exec(query);
        __count_users = std::stoi(response[0][0].c_str());
    }
    catch(std::exception const &e){
        std::cout << e.what() << '\n';
    }
}

