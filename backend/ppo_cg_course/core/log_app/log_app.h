#ifndef _LOG_APP_H_
#define _LOG_APP_H_

#include <iostream>
#include <fstream>

#include "log_structs.h"

class LogApp
{
    public:
        LogApp();
        ~LogApp();

        void write_log_info(log_info_t &log_info);

    private:
        std::string _path_log_info_user = "../ppo_cg_course/log_data/log_user.txt";
};

#endif
