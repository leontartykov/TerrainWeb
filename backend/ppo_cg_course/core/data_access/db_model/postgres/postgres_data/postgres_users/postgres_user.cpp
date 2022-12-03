#include "postgres_user.h"

UserPostgres::UserPostgres(std::shared_ptr<pqxx::connection> &conn_psql){
    __conn_psql = conn_psql;
    __define_count_users();
}

int UserPostgres::get(const int &id, dbUsers_t &user)
{
    int ret_code = SUCCESS;
    if (id <= 0 || id >= __count_users){
        ret_code = NOT_FOUND;
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

    return ret_code;
}

int UserPostgres::get_count_users(){
    return __count_users;
}

int UserPostgres::add(const dbUsers_t &user)
{
    std::string query;
    pqxx::result response;
    int userId;

    if (!__conn_psql){
        std::cout << "Ошибка: нет подключения к БД." << std::endl;
        return CONNECTION_FAILED;
    }
    else if (__is_user_empty(user) || user.perm_level == 0){
        std::cout << "О пользователе нет данных.\n";
        return BAD_REQUEST;
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
            userId = __count_users;
            __count_users++;

            query = "INSERT INTO terrain_project.users.info values (" + \
                                std::to_string(userId) + ", '" +
                                user.login + "', '" + user.password + "', " + std::to_string(user.perm_level) +
                                ", false, " + "false)";
        }
        worker.exec(query);
        worker.commit();
        std::cout << "Пользователь был добавлен успешно.\n";
    }
    catch (std::exception const &e){
        std::cout << e.what() << '\n';
        return BAD_REQUEST;
    }

    std::cout << "\nДобавление в psql произошло успешно.\n";

    return SUCCESS_CREATED;
}

int UserPostgres::delete_user(const int &id)
{
    int success = SUCCESS;
    if (!__conn_psql){
        std::cout << "Нет подключения к БД." << std::endl;
        success = CONNECTION_FAILED;
    }
    else if (id <= 0 || id >= __count_users){
        std::cout << "О пользователе нет данных (ID).\n";
        success = NOT_FOUND;
    }
    else{
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
            return BAD_REQUEST;
        }
    }

    return success;
}

int UserPostgres::update(const int &id, const dbUsers_t &user)
{
    dbUsers_t del_user;
    std::string query;
    int ret_code = SUCCESS;

    if (!__conn_psql){
        std::cout << "Нет подключения к БД." << std::endl;
        ret_code = CONNECTION_FAILED;
    }
    else if (id <= 0 || id >= __count_users){
        ret_code = NOT_FOUND;
    }
    else{
        try{
                pqxx::work worker(*__conn_psql);
                query = "UPDATE terrain_project.users.info SET login = '" + \
                                    user.login + "' WHERE id = '" + std::to_string(id) + "';";
                worker.exec(query);
                worker.commit();
                std::cout << "\nЛогин обновлен успешно.\n";
        }
        catch(std::exception const &e){
            std::cerr << e.what() << '\n';
            ret_code = BAD_REQUEST;
        }
    }

    return ret_code;
}

int UserPostgres::block(const int &id)
{
    int ret_code = SUCCESS;
    if (!__conn_psql){
        std::cout << "Нет подключения к БД." << std::endl;
        ret_code = CONNECTION_FAILED;
    }
    else if (id <= 0 || id >= __count_users){
        ret_code = NOT_FOUND;
    }
    else{
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
            return BAD_REQUEST;
        }
    }

    return ret_code;
}

int UserPostgres::unlock(const int &id)
{
    int ret_code = SUCCESS;
    if (!__conn_psql){
        std::cout << "Нет подключения к БД." << std::endl;
        ret_code = CONNECTION_FAILED;
    }
    else if (id <= 0 || id >= __count_users){
        ret_code = NOT_FOUND;
    }
    else{
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
            return BAD_REQUEST;
        }
    }

    return ret_code;
}

int UserPostgres::get_validation(dbUsers_t &user)
{
    std::string query;
    pqxx::result response;
    int success = SUCCESS;

    if (user.login.empty() || user.password.empty()){
        return BAD_REQUEST;
    }

    try{
        pqxx::work worker(*__conn_psql);
        query = "SELECT info.id, info.blocked, info.deleted " \
                "FROM terrain_project.users.info as info " \
                "WHERE info.login = '" + user.login + "' AND info.password = '" + user.password + "';";
        response = worker.exec(query);
        if (response.empty()){
            success = NOT_FOUND;
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

bool UserPostgres::__is_user_empty(const dbUsers_t &user){
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

