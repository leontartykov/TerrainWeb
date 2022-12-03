#ifndef _HTTP_SERVER_HPP_
#define _HTTP_SERVER_HPP_

#include <drogon/drogon.h>

#include "http_server/controllers/http_controllers.hpp"
#include "core/data_access/db_model/base_db_model.hpp"
#include "core/data_access/db_model/postgres/postgres.hpp"

enum rdbms {postgresql, mysql};

class HttpServer10
{
    private:
        std::shared_ptr<api::v1::UsersController> __usersController;
        api::v1::TerrainsController __terrainsController;

        Config __config;

        std::shared_ptr<DbModel> __dbModel;
        std::shared_ptr<DbModel> __create_db_model(config_t &config);

    public:
        HttpServer10();
        ~HttpServer10() = default;

        void run_server();

};

#endif
