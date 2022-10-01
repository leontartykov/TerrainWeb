# include "entry.h"
#include "../exceptions/base_error.h"

EntrySystem::EntrySystem(){
    _current_time = time(NULL);
}

EntrySystem::~EntrySystem(){
}

int EntrySystem::_verify_user(user_info_t &user){
    int error = 0;
    try
    {
        config_t config_data = _config.read_config_file_postgres();
        std::string options = _config.form_options(config_data);
        _connect = std::unique_ptr<pqxx::connection>(
                    new pqxx::connection(options));
    }
    catch (std::exception const &e){
        log_info_t log_info_exception = {
            .type_log = "error",
            .file_name = __FILE__,
            .class_name = typeid(*this).name(),
            .function_name = __FUNCTION__,
            .line_error = __LINE__,
            .time_error = ctime(&_current_time),
            .message_error = "ошибка идентификации пользователя; соединение с БД не установлено.",
            .number_error = -1,
            .user_login = user.login
        };

        throw BaseError(log_info_exception);

        return -1;
    }

    pqxx::work worker(*_connect);
    pqxx::result R {worker.exec(
                    "SELECT * FROM ppo.passwords.users "
                    "WHERE users.login = '" + user.login + "' "
                    "AND users.password = '" + user.password + "';")};

    if (R.size() == 0){
        error = 1;
        std::cout << "Ошибка идентификации: пользователь не найден." << std::endl;
        log_info_t log_info_exception = {
            .type_log = "error",
            .file_name = __FILE__,
            .class_name = typeid(*this).name(),
            .function_name = __FUNCTION__,
            .line_error = __LINE__,
            .time_error = ctime(&_current_time),
            .message_error = "ошибка идентификации: пользователь не найден.",
            .number_error = 1,
            .user_login = user.login
        };
        LogApp log_app;
        log_app.write_log_info(log_info_exception);
    }

    _connect->disconnect();
    return error;
}

int EntrySystem::enter_system(){
    user_info_t user_info;
    int error = 1;

    while (error >= 0)
    {
        std::cout << "Вход в систему." << std::endl;

        std::cout << "Логин:";
        std::cin >> user_info.login;

        std::cout << "Пароль:";
        std::cin >> user_info.password;

        error = this->_verify_user(user_info);

        if (error == 0)
        {
            log_info_t log_info_exception;
            log_info_exception.type_log = "info";
            log_info_exception.message_error = "подключение пользователя.";
            log_info_exception.user_login = user_info.login;
            log_info_exception.time_error = ctime(&_current_time);

            LogApp log_app;
            log_app.write_log_info(log_info_exception);

            if (user_info.login.compare("admin") == 0){
                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseUser> user = admin;
                user->set_user_login(user_info.login);
                error = user->do_action();
            }
            else{
                std::shared_ptr<User> con_user(new User());
                std::shared_ptr<BaseUser> user = con_user;
                user->set_user_login(user_info.login);
                error = user->do_action();
            }
        }
    }

    return error;
}
