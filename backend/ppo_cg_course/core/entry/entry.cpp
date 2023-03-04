# include "entry.h"
#include <QDebug>
#include "core/exceptions/base_error.h"

EntrySystem::EntrySystem(){
    __dbModel = std::make_shared<Postgres>();
    _current_time = time(NULL);
}

EntrySystem::~EntrySystem(){
}

int EntrySystem::_verify_user(user_info_t &user){
    std::string query, options;
    config_t config_data;
    int success = SUCCESS;

    try
    {
        std::cerr << "success: " << success << "\n";
        success = _config.read_config_postgres(config_data);
        std::cerr << "success: " << success << "\n";
        if (success == SUCCESS){
            options = _config.form_options(config_data);
            _connect = std::unique_ptr<pqxx::connection>(
                        new pqxx::connection(options));
        }
    }
    catch (std::exception const &e){
        log_info_t log_info_exception = {
            .type_log = "error",
            .file_name = __FILE__,
            .class_name = typeid(*this).name(),
            .function_name = __FUNCTION__,
            .line_error = __LINE__,
            .time_error = ctime(&_current_time),
            .message_error = "соединение с БД не установлено.",
            .number_error = -1,
            .user_login = user.login
        };
        std::cerr << e.what() << std::endl;
        throw BaseError(log_info_exception);

        return -1;
    }

    pqxx::work worker(*_connect);
    query = "SELECT * FROM terrain_project.users.info "
            "WHERE login = '" + user.login + "' "
            "AND password = '" + user.password + "';";

    pqxx::result R {worker.exec(query)};

    if (R.size() == 0){
        success = 1;
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
    return success;
}

servUsers_t EntrySystem::__input_user_info()
{
    servUsers_t user;

    std::cout << "Вход в систему." << "\n";

    std::cout << "Логин: ";
    std::cin >> user.login;

    std::cout << "Пароль: ";
    std::cin >> user.password;

    return user;
}

int EntrySystem::enter_system(){
    servUsers_t userInfo;
    int ret_code = 1;
    log_info_t log_info_exception;
    LogApp log_app;

    try{
        while (ret_code >= SUCCESS)
        {
            userInfo = __input_user_info();
            std::cerr << "ret_code: " << ret_code << "\n";
            ret_code = __dbModel->login(userInfo.login, userInfo.password);
            std::cerr << "ret_code: " << ret_code << "\n";

            if (ret_code == SUCCESS)
            {
                log_info_exception.type_log = "info";
                log_info_exception.message_error = "подключение пользователя.";
                log_info_exception.user_login = userInfo.login;
                log_info_exception.time_error = ctime(&_current_time);

                log_app.write_log_info(log_info_exception);

                if (userInfo.login.compare("admin") == 0){
                    std::shared_ptr<Admin> admin(new Admin());
                    std::shared_ptr<BaseAppUser> user = admin;
                    user->set_user_login(userInfo.login);
                    ret_code = user->do_action();
                }
                else{
                    std::shared_ptr<User> con_user(new User());
                    std::shared_ptr<BaseAppUser> user = con_user;
                    user->set_user_login(userInfo.login);
                    ret_code = user->do_action();
                }
            }
        }
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
    }

    return ret_code;
}
