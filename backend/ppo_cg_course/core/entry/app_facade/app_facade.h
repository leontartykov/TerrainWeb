#ifndef _APP_FACADE_H_
#define _APP_FACADE_H_

#include "../app_command/app_command_base.h"

class AppFacade{
    public:
        AppFacade() = default;
        ~AppFacade() = default;
        void execute(std::shared_ptr<BaseAppCommand> cmd);
};

#endif
