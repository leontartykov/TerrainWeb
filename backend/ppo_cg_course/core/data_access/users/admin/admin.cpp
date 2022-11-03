#include "admin.h"
#include "../../../entry/app_command/app_command.h"

Admin::Admin(){
    _current_time = time(NULL);
    _connect_psql = nullptr;
    _connect_mysql = nullptr;

    this->_connect_psql_to_db();

    //this->_connect_mysql_to_db();

    _app_facade = std::shared_ptr<AppFacade>(new AppFacade());
}

Admin::~Admin(){
    this->disconnect_db();
}

int Admin::add_user(users_t &user){
    return __add_user_psql(user);
}

int Admin::_connect_psql_to_db()
{
    if (_connect_psql){
        std::cout << "Уже есть подключение к БД.\n";
        return -1;
    }

    try
    {
        config_t config_data = _config.read_config_file_postgres();
        std::string options = _config.form_options(config_data);
        _connect_psql = std::shared_ptr<pqxx::connection>(
                    new pqxx::connection(options));
        __postgres.set_psql_connection(_connect_psql);

    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        return -2;
    }

    return 0;
}

int Admin::_connect_mysql_to_db()
{
    if (_connect_mysql){
        std::cout << "Уже есть подключение к БД.\n";
        return -1;
    }

    try
    {
        config_t config_data = _config.read_config_file_mysql();
        sql::mysql::MySQL_Driver *driver;

        driver = sql::mysql::get_mysql_driver_instance();
        _connect_mysql = driver->connect(config_data.host, config_data.user, config_data.password);
    }
    catch (std::exception const &e){
        std::cerr << e.what() << '\n';
        return -2;
    }

    return 0;
}

int Admin::disconnect_db()
{
    if (_connect_psql){
        _connect_psql->disconnect();
        _connect_psql = nullptr;
        std::cout << "Отключение от psql проведено успешно.\n";
    }
    else{
        std::cout << "Не было подключения к БД psql.\n";
    }

    if (_connect_mysql){
        _connect_mysql->close();
        _connect_mysql = nullptr;
        std::cout << "Отключение от mysql проведено успешно.\n";
    }
    else{
        std::cout << "Не было подключения к БД mysql.\n";
    }

    return 0;
}

int Admin::__add_user_psql(users_t &user){
    int http_response_code =  __postgres.do_action_users(users_action::add_u, user);
    return http_response_code;
}

int Admin::_add_user_mysql(users_t &user)
{
    /*if (!_connect_mysql){
        std::cout << "error: Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -2;
    }
   try{
        sql::Statement *stmt;
        stmt = _connect_mysql->createStatement();
        stmt->execute("use ppo");
        stmt->execute("insert into ppo.users (login, password) values ('" + user.login + "', '" + user.password + "')");
    }
    catch (std::exception const &e){
        std::cout << e.what() << '\n';
        return -3;
    }

    std::cout << "Добавление в mysql произошло успешно.\n";*/

    return 0;
}

int Admin::delete_user(users_t &user)
{
    int error;
    error = __delete_user_psql(user);
    //error = __delete_user_mysql(user);
    return error;
}

int Admin::__delete_user_psql(users_t &user){
    int http_response_code = __postgres.do_action_users(users_action::delete_u, user);

    return http_response_code;
}

int Admin::_delete_user_mysql(users_t &user)
{
    /*if (!_connect_mysql){
        std::cout << "Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -2;
    }

    try{
        sql::Statement *stmt;
        sql::ResultSet  *res;
        users_t del_user;
        stmt = _connect_mysql->createStatement();
        stmt->execute("use ppo");
        res = stmt->executeQuery("select * from ppo.users where login = '" + user.login + "';");
        res->next();del_user.login = res->getString("login");
        del_user.password = res->getString("password");
        del_user.is_blocked = res->getString("locked");

        stmt->execute("insert into ppo.deleted_users (login, password, locked) values ('" + del_user.login + "', '" + del_user.password + "', " + del_user.is_blocked + ");");
        stmt->execute("delete from ppo.users where login = '" + user.login + "';");
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }*/

    return 0;
}

int Admin::lock_user(users_t &user){
    int http_response_code = __postgres.do_action_users(users_action::block_u, user);

    return http_response_code;
}

int Admin::unlock_user(users_t &user)
{
    int http_response_code = __postgres.do_action_users(users_action::unlock_u, user);

    return http_response_code;
}

int Admin::check_connection(){
    if (!_connect_psql){
        std::cout << "Подключение к psql не установлено.\n";
        return -1;
    }
    else{
        std::cout << "Подключение к psql установлено.\n";
    }

    if (_connect_psql->is_open()){
        return 1;
    }

    return 0;
}

void Admin::set_user_login(std::string &usr_login){
    user_login = usr_login;
}
