#include "config.h"
#include "error_codes.h"

Config::Config(){
    __old_config_path = "../ppo_cg_course/config_data/config.json";
    __config_path = "../ppo_cg_course/http_server/config.json";
}

///Old version
config_t Config::read_config_file_postgres()
{
    config_t config_data;
    std::ifstream config_file;
    Json::Reader reader;
    Json::Value root;

    config_file.open(__old_config_path);
    reader.parse(config_file, root);

    if (root["PostgreSQL"] == 1)
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

int Config::read_config_postgres(config_t &config_data)
{
    int success = SUCCESS;
    std::ifstream config_file;
    Json::Reader reader;
    Json::Value root;

    try{
        std::cerr << "read\n";
        config_file.open(__config_path);

        reader.parse(config_file, root);

        if (root["db_clients"] == 1)
        {
            config_data.name_db_client = root["db_clients"][0]["name"].asString().c_str();
            config_data.dbms_type = root["db_clients"][0]["rdbms"].asString().c_str();
            config_data.db_name = root["db_clients"][0]["dbname"].asString().c_str();
            config_data.host = root["db_clients"][0]["host"].asString().c_str();
            config_data.user = root["db_clients"][0]["user"].asString().c_str();
            config_data.password = root["db_clients"][0]["password"].asString().c_str();
            config_data.port = root["db_clients"][0]["port"].asString().c_str();
        }
        config_file.close();
    }
    catch(std::exception &e){
        std::cerr << e.what() << "\n";
        return ERR_CONFIG;
    }

    return success;
}

config_t Config::read_config_file_mysql()
{
    config_t config_data;
    std::ifstream config_file;
    Json::Reader reader;
    Json::Value root;

    config_file.open(__old_config_path);
    reader.parse(config_file, root);

    if (root["MySQL"] == 1)
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
