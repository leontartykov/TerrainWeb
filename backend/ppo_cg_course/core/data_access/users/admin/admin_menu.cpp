#include "admin.h"
#include "../../../log_app/log_app.h"

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
        std::cout << "Введите пункт меню:";
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
            case menu::ADD_USER:
            {
                users_t user;
                std::cout << "Введите id пользователя: ";
                std::cin >> user.id;
                std::cout << "user.id: " << user.id << std::endl;

                std::cout << "Введите логин: ";
                std::cin >> user.login;

                std::cout << "Введите пароль: ";
                std::cin >> user.password;

                user.is_blocked = false;
                user.is_deleted = false;

                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> add_user_cmd(
                           new AppUserCmd<Admin>(admin, &Admin::add_user, user));
                _app_facade->execute(add_user_cmd);

                break;
            }
            case menu::DELETE_USER:
            {
                users_t user;
                std::cout << "Введите id пользователя: ";
                std::cin >> user.id;

                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> delete_user_cmd(
                           new AppUserCmd<Admin>(admin, &Admin::delete_user, user));
                _app_facade->execute(delete_user_cmd);
                break;
            }
            case menu::LOCK_USER:
            {
                users_t user;
                std::cout << "Введите id пользователя: ";
                std::cin >> user.id;

                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> lock_user_cmd(
                           new AppUserCmd<Admin>(admin, &Admin::lock_user, user));
                _app_facade->execute(lock_user_cmd);
                break;
            }
            case menu::UNLOCK_USER:
            {
                users_t user;
                std::cout << "Введите id пользователя: ";
                std::cin >> user.id;

                std::shared_ptr<Admin> admin(new Admin());
                std::shared_ptr<BaseAppCommand> lock_user_cmd(
                           new AppUserCmd<Admin>(admin, &Admin::unlock_user, user));
                _app_facade->execute(lock_user_cmd);
            break;
            }
             default:
                std::cout << " Неизвестная команда.\n";
                break;
        }
    }

    return number;
}
