#include "admin.h"
#include "../../../entry/app_command/app_command.h"
#include "../../../log_app/log_app.h"

Admin::Admin(){
    _current_time = time(NULL);
    _connect_psql = nullptr;
    _connect_mysql = nullptr;

    this->_connect_psql_to_db();
    this->_connect_mysql_to_db();

    _app_facade = std::shared_ptr<AppFacade>(new AppFacade());
}

Admin::~Admin(){
    this->disconnect_db();
}

int Admin::_connect_psql_to_db()
{
    if (_connect_psql){
        std::cout << "Уже есть подключение к БД.\n"  << std::endl;
        return -1;
    }

    try
    {
        config_t config_data = _config.read_config_file_postgres();
        std::string options = _config.form_options(config_data);
        _connect_psql = std::unique_ptr<pqxx::connection>(
                    new pqxx::connection(options));
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
        std::cout << "Уже есть подключение к БД.\n"  << std::endl;
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
        std::cout << "Отключение от psql проведено успешно." << std::endl;
    }
    else{
        std::cout << "Не было подключения к БД psql." << std::endl;
    }

    if (_connect_mysql){
        _connect_mysql->close();
        _connect_mysql = nullptr;
        std::cout << "Отключение от mysql проведено успешно." << std::endl;
    }
    else{
        std::cout << "Не было подключения к БД mysql." << std::endl;
    }

    return 0;
}

int Admin::_is_user_empty(users_t &user){
    int error = 0;
    if (user.password.empty() && user.login.empty()){
        error = -1;
    }

    return error;
}

int Admin::add_user(users_t &user)
{
    int error = this->_add_user_psql(user);
    error = this->_add_user_mysql(user);
    return error;
}

int Admin::_add_user_psql(users_t &user)
{
    if (!_connect_psql){
        std::cout << "error: Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -2;
    }
   try{
        pqxx::work worker(*_connect_psql);

        worker.exec("insert into ppo.passwords.users values ('" + user.login + "', '" + user.password + "', false, " + "false)");
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

int Admin::_add_user_mysql(users_t &user)
{
    if (!_connect_mysql){
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

    std::cout << "Добавление в mysql произошло успешно.\n";

    return 0;
}

int Admin::delete_user(users_t &user)
{
    int error;// = this->_delete_user_psql(user);
    error = this->_delete_user_mysql(user);
    return error;
}

int Admin::_delete_user_psql(users_t &user)
{
    if (!_connect_psql){
        std::cout << "Нет подключения к БД." << std::endl;
        return -1;
    }
    else if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -2;
    }

    try{
        users_t del_user;
        pqxx::work worker(*_connect_psql);
        pqxx::result response = worker.exec("SELECT * FROM ppo.passwords.users WHERE login = '" + user.login + "';");

        del_user.login = response[0][0].c_str();
        del_user.password = response[0][1].c_str();
        del_user.is_blocked = response[0][2].c_str();

        worker.exec("DELETE FROM ppo.passwords.users WHERE login = '" + user.login + "';");
        worker.exec("insert into ppo.passwords.deleted_users values ('" + del_user.login + "', '" + del_user.password + "', false);");
        //worker.exec("UPDATE ppo.passwords.users SET delete = true WHERE login = '" + user.login + "';");
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int Admin::_delete_user_mysql(users_t &user)
{
    if (!_connect_mysql){
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
    }

    return 0;
}

int Admin::lock_user(users_t &user)
{
    if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -1;
    }

    try{
        pqxx::work worker(*_connect_psql);
        worker.exec("UPDATE ppo.passwords.users SET lock = true WHERE login LIKE '%" + user.login + "';");
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int Admin::unlock_user(users_t &user)
{
    if (this->_is_user_empty(user) != 0){
        std::cout << "О пользователе нет данных.\n";
        return -1;
    }

    try{
        pqxx::work worker(*_connect_psql);
        worker.exec("UPDATE ppo.passwords.users SET lock = false WHERE login LIKE '%" + user.login + "';");
        worker.commit();
    }
    catch(std::exception const &e){
        std::cerr << e.what() << '\n';
        return -3;
    }

    return 0;
}

int Admin::check_connection(){
    if (!_connect_psql){
        std::cout << "Подключение не установлено." << std::endl;
        return -1;
    }

    if (_connect_psql->is_open()){
        return 1;
    }

    return 0;
}

void Admin::show_menu(){
    std::cout << "1. Запустить приложение.\n";
    std::cout << "2. Добавить пользователя.\n";
    std::cout << "3. Удалить пользователя.\n";
    std::cout << "4. Заблокировать пользователя.\n";
    std::cout << "5. Разблокировать пользователя.\n";
    std::cout << "0. Выйти.\n";
    std::cout << std::endl;
}

int Admin::do_action()
{
    this->show_menu();
    int number = -1;
    while (number != 0)
    {
        std::cout << "Введите пункт меню:\n";
        std::cin >> number;
        std::cout << "number: " << number << std::endl;

        switch (number)
        {
            case menu::QUIT:
                std::cout << "quit application.\n";
                break;
            case menu::LAUNCH:
            {
                log_info_t log_info_exception;
                log_info_exception.type_log = "info";
                log_info_exception.message_error = "запуск приложения.";
                log_info_exception.user_login = user_login;
                log_info_exception.time_error = ctime(&_current_time);

                LogApp log_app;
                log_app.write_log_info(log_info_exception);

                std::shared_ptr<LaunchAppCmd> launch_cmd(new LaunchAppCmd());
                std::shared_ptr<BaseAppCommand> base_launch_cmd = launch_cmd;
                _app_facade->execute(base_launch_cmd);
                break;
            }
            case menu::ADD_USER:
            {
                //переделать
                std::cout << "Функция недступна.\n";
                break;
                users_t user;
                user.login = "user12";
                user.password = "qwwer";
                user.is_blocked = false;
                std::shared_ptr<Admin> admin(new Admin());
                std::cout << "проверка соединения: " << admin->check_connection();
                std::shared_ptr<BaseAppCommand> add_user_cmd(
                           new AppAddUserCmd<Admin>(admin, &Admin::add_user, user));
                _app_facade->execute(add_user_cmd);

                break;
            }
            case menu::DELETE_USER:
            {
                //переделать
                std::cout << "Функция недступна.\n";
                break;
                users_t user;
                user.login = "user12";
                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> delete_user_cmd(
                           new AppAddUserCmd<Admin>(admin, &Admin::delete_user, user));
                _app_facade->execute(delete_user_cmd);
                break;
            }
            case menu::LOCK_USER:
            {
                //переделать
                std::cout << "Функция недступна.\n";
                break;
                users_t user;
                user.login = "user12";
                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> lock_user_cmd(
                           new AppAddUserCmd<Admin>(admin, &Admin::lock_user, user));
                _app_facade->execute(lock_user_cmd);
                std::cout << "lock_user.\n";
                break;
            }
            case menu::UNLOCK_USER:
            {
                //переделать
                std::cout << "Функция недступна.\n";
                break;
                users_t user;
                user.login = "user12";
                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> lock_user_cmd(
                           new AppAddUserCmd<Admin>(admin, &Admin::unlock_user, user));
                _app_facade->execute(lock_user_cmd);
                std::cout << "lock_user.\n";
            break;
            }
             default:
                std::cout << " Неизвестная команда.\n";
                break;
        }
    }

    return number;
}

void Admin::set_user_login(std::string &usr_login){
    user_login = usr_login;
}
