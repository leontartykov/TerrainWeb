#ifndef _APP_COMMAND_H_
#define _APP_COMMAND_H_

#include <QApplication>
#include "app_command_base.h"
#include "http_server/services/user/struct_users_service.hpp"
#include "core/gui/main_window.h"


class LaunchAppCmd: public BaseAppCommand
{
    private:
        int _execute();
    public:
        LaunchAppCmd() = default;
        ~LaunchAppCmd() = default;
        virtual void execute() override;
};

template <typename Receiver>
class AppUserCmd: public BaseAppCommand
{
    private:
        typedef int(Receiver::*Action)(const servUsers_t&);

        std::shared_ptr<Receiver> receiver;
        Action action;
        servUsers_t user;

    public:
        AppUserCmd(std::shared_ptr<Receiver> r, Action a, const servUsers_t u): receiver(r), action(a), user(u) {}
        virtual void execute() override {((*receiver).*action)(user);}
};

#endif
