#include "config.h"

Config::Config(){
    _config_path = "../ppo_cg_course/config_data/config.json";
}

config_t Config::read_config_file_postgres()
{
    config_t config_data;
    std::ifstream config_file;
    config_file.open(_config_path);
    Json::Reader reader;
    Json::Value root;
    reader.parse(config_file, root);

    if (root["PostgreSQL"])
    {
        config_data.dbms_type = "PostgreSQL";
        config_data.db_name = root["PostgreSQL"]["db_name"].asString().c_str();
        config_data.host = root["PostgreSQL"]["host"].asString().c_str();
        config_data.user = root["PostgreSQL"]["user"].asString().c_str();
        config_data.password = root["PostgreSQL"]["password"].asString().c_str();
        config_data.port = root["PostgreSQL"]["port"].asString().c_str();
    }

    config_file.close();

    return config_data;
}

config_t Config::read_config_file_mysql()
{
    config_t config_data;
    std::ifstream config_file;
    config_file.open(_config_path);
    Json::Reader reader;
    Json::Value root;
    reader.parse(config_file, root);

    if (root["MySQL"])
    {
        config_data.dbms_type = "MySQL";
        config_data.db_name = root["MySQL"]["db_name"].asString().c_str();
        config_data.host = root["MySQL"]["host"].asString().c_str();
        config_data.user = root["MySQL"]["user"].asString().c_str();
        config_data.password = root["MySQL"]["password"].asString().c_str();
        config_data.port = root["MySQL"]["port"].asString().c_str();
    }

    config_file.close();

    return config_data;
}

std::string Config::form_options(config_t &config_data)
{
    std::string options;
    options += "host = "; options += config_data.host;
    options += " port = "; options += config_data.port;
    options += " user = "; options += config_data.user;
    options += " password = "; options += config_data.password;
    options += " dbname = "; options += config_data.db_name;

    return options;
}
