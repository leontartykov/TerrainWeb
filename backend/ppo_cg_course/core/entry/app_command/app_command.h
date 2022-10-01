#ifndef _APP_COMMAND_H_
#define _APP_COMMAND_H_

#include <QApplication>
#include "app_command_base.h"
#include "../../data_access/users/users_struct.h"
#include "../../gui/main_window.h"

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
class AppAddUserCmd: public BaseAppCommand
{
    private:
        typedef int(Receiver::*Action)(users_t&);

        std::shared_ptr<Receiver> receiver;
        Action action;
        users_t user;

    public:
        AppAddUserCmd(std::shared_ptr<Receiver> r, Action a, users_t u): receiver(r), action(a), user(u) {}
        virtual void execute() override {((*receiver).*action)(user);}
};

#endif
