#include "users.h"
#include "./core/log_app/log_app.h"

User::User(){
    _current_time = time(NULL);
    _app_facade = std::shared_ptr<AppFacade>(new AppFacade());
}

void User::show_menu(){
    std::cout << "1. Запустить приложение.\n";
    std::cout << "0. Выйти.\n\n";
}

int User::do_action()
{
    this->show_menu();
    int number = -1;
    while (number != 0)
    {
        std::cout << "Введите пункт меню:\n";
        std::cin >> number;

        switch (number)
        {
            case menu::QUIT:
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
        }
    }

    return number;
}

void User::set_user_login(std::string &usr_login){
    user_login = usr_login;
}
