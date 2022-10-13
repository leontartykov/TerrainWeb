#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <fstream>
#include <string>

#include "config_struct.h"

class Config
{
    private:
        std::string _config_path;

    public:
        Config();
        ~Config() = default;

        config_t read_config_file_postgres();
        config_t read_config_file_mysql();

        std::string form_options(config_t &config_data);
};

#endif
