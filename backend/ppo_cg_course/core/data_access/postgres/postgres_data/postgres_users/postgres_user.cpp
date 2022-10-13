#include "postgres_user.h"

UserPostgres::UserPostgres(){
    __count_users = 1;
}

users_t UserPostgres::get(int &id)
{
    users_t res_user;
    pqxx::work worker(*__conn_psql);
    std::string query = "SELECT * FROM terrain_project.users.passwords WHERE id = '" + \
                         std::to_string(id) + "';";

    pqxx::result response = worker.exec(query);

    res_user.id = std::stoi(response[0][0].c_str());
    res_user.login = response[0][1].c_str();
    res_user.password = response[0][2].c_str();
    res_user.is_blocked = response[0][3].c_str();
    res_user.is_deleted = response[0][4].c_str();

    return res_user;
}

int UserPostgres::add(users_t &user)
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
        query = "SELECT * from terrain_project.users.passwords where login like '%" \
                 + user.login + "'";
        response = worker.exec(query);

        if (!response.empty()){
            query = "UPDATE terrain_project.users.passwords SET deleted = false";
        }
        else
        {
            __count_users++;

            query = "INSERT INTO terrain_project.users.passwords values (" + \
                                std::to_string(user.id) + ", '" +
                                user.login + "', '" + user.password + "', false, " + "false)";
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
        std::string query = "UPDATE terrain_project.users.passwords SET deleted = true WHERE id = '" + \
                            std::to_string(id) + "';";
        worker.exec(query);
        worker.commit();

        std::cout << "\nУдаление пользователя выполнена успешно.\n";
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int UserPostgres::update_login(int &id, std::string &new_login)
{
    try{
        users_t del_user;
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.passwords SET login = " + \
                            new_login + " WHERE id = '" + std::to_string(id) + "';";
        worker.exec(query);
        worker.commit();
        std::cout << "\nЛогин обновлен успешно.\n";
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int UserPostgres::block(int &id)
{
    if (!id){
        std::cout << "О пользователе нет данных.\n";
        return -1;
    }

    try{
        pqxx::work worker(*__conn_psql);
        std::string query = "UPDATE terrain_project.users.passwords SET blocked = true WHERE id = " \
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
        std::string query = "UPDATE terrain_project.users.passwords SET blocked = false WHERE id = " \
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
        std::cout << "Отключение от psql проведено успешно.\n";
    }
    else{
        std::cout << "Не было подключения к БД psql.\n";
    }
}

void UserPostgres::set_psql_connection(std::shared_ptr<pqxx::connection> &conn_psql){
    __conn_psql = conn_psql;
}
