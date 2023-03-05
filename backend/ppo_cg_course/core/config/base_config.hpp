#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include "config_struct.h"

class IConfig
{
    public:
        virtual ~IConfig() {};

        virtual config_t read_config_file_postgres() = 0;
        virtual config_t read_config_file_mysql() = 0;

        virtual std::string form_options(config_t &config_data) = 0;
        virtual config_t read_config_postgres() = 0;
};

#endif
