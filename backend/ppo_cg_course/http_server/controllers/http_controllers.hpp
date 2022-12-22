#ifndef _HTTP_CONTROLLERS_HPP_
#define _HTTP_CONTROLLERS_HPP_

#include <drogon/HttpController.h>

#include "core/config/config.h"
#include "core/data_access/db_model/base_db_model.hpp"
#include "http_server/services/user/users_service.hpp"
#include "http_server/services/base_terrain_service.hpp"
#include "http_server/services/base_user_service.hpp"
#include "http_server/json_former/json_former.hpp"

using namespace drogon;

namespace api
{
    namespace v1
    {
        std::shared_ptr<DbModel> create_db_model(config_t &config);

        class TerrainSessions: public UserSessions {};

        class UsersController : public drogon::HttpController<UsersController>
        {
            private:
                std::shared_ptr<IUserService> __users_service;

                Config __config;

            public:
                UsersController();
                ~UsersController();

                METHOD_LIST_BEGIN
                    ADD_METHOD_TO(UsersController::get_info, "api/v1/users/{1}", Get);
                    ADD_METHOD_TO(UsersController::add_new, "api/v1/accounts/register", Post, Options);
                    ADD_METHOD_TO(UsersController::delete_usr, "api/v1/users/{1}", Delete, Options);
                    ADD_METHOD_TO(UsersController::change_usr_login, "api/v1/users/{1}", Patch, Options);
                    ADD_METHOD_TO(UsersController::login, "api/v1/accounts/login", Post, Options);
                METHOD_LIST_END

                void get_info(const HttpRequestPtr &req,
                              std::function<void (const HttpResponsePtr &)> &&callback,
                              std::string userId);
                void add_new(const HttpRequestPtr &req,
                             std::function<void (const HttpResponsePtr &)> &&callback);
                void delete_usr(const HttpRequestPtr &req,
                                std::function<void (const HttpResponsePtr &)> &&callback,
                                std::string userId);
                void change_usr_login(const HttpRequestPtr &req,
                                std::function<void (const HttpResponsePtr &)> &&callback,
                                std::string userId);
                void login(const HttpRequestPtr &req,
                                      std::function<void (const HttpResponsePtr &)> &&callback);
                void set_dbModel(std::shared_ptr<DbModel> dbModel);

        };

        class TerrainsController : public drogon::HttpController<TerrainsController>
        {
            private:
                std::shared_ptr<ITerrainService> __terrains_service;

                TerrainSessions __sessions;
                Config __config;

                std::pair<dbTerrain_t, light_t>
                    __handle_json_body(std::shared_ptr<Json::Value> jsonBodyIn);

            public:
                TerrainsController();
                METHOD_LIST_BEGIN
                    ADD_METHOD_TO(TerrainsController::get_all_terrain_projects, "api/v1/users/{1}/projects?page={2}", Get, Options);
                    ADD_METHOD_TO(TerrainsController::add_new_project, "api/v1/users/{1}/projects", Post, Options);
                    ADD_METHOD_TO(TerrainsController::get_terrain_params, "api/v1/users/{1}/projects/{2}/values", Get);
                    ADD_METHOD_TO(TerrainsController::find_project, "api/v1/users/{1}/projects/{2}", Get);
                    ADD_METHOD_TO(TerrainsController::delete_terrain_project, "api/v1/users/{1}/projects/{2}", Delete, Options);
                    ADD_METHOD_TO(TerrainsController::get_rating_terrain_project, "api/v1/ratingJobs/terrain/{id}/rate", Get, Options);
                    ADD_METHOD_TO(TerrainsController::set_rating_terrain_project, "api/v1/ratingJobs/terrain/{id}/rate", Post, Options);
                    ADD_METHOD_TO(TerrainsController::get_render_image, "api/v1/renderJobs/terrains/image", Post, Options);
                METHOD_LIST_END

                void get_all_terrain_projects(const HttpRequestPtr &req,
                              std::function<void (const HttpResponsePtr &)> &&callback,
                              std::string userId, std::string page);
                void add_new_project(const HttpRequestPtr &req,
                              std::function<void (const HttpResponsePtr &)> &&callback,
                              std::string userId);
                void get_terrain_params(const HttpRequestPtr &req,
                              std::function<void (const HttpResponsePtr &)> &&callback,
                              std::string userId, std::string terrainId);
                void find_project(const HttpRequestPtr &req,
                                  std::function<void (const HttpResponsePtr &)> &&callback,
                                  std::string userId, std::string projName);

                void delete_terrain_project(const HttpRequestPtr &req,
                              std::function<void (const HttpResponsePtr &)> &&callback,
                              std::string userId, std::string projName);
                void get_rating_terrain_project(const HttpRequestPtr &req,
                              std::function<void (const HttpResponsePtr &)> &&callback,
                              std::string terrainId);
                void set_rating_terrain_project(const HttpRequestPtr &req,
                              std::function<void (const HttpResponsePtr &)> &&callback,
                              std::string terrainId);
                void get_render_image(const HttpRequestPtr &req,
                              std::function<void (const HttpResponsePtr &)> &&callback);
                void set_dbModel(std::shared_ptr<DbModel> dbModel);

        };


    }
}

#endif
