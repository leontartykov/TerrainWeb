#ifndef _POSTGRES_H_
#define _POSTGRES_H_

#include "../postgres_data/postgres_users/postgres_user.h"
#include "../postgres_data/postgres_terrains/postgres_terrains.h"
#include "../../../config/config.h"

///actions with users
enum users_action{
    add_u,
    get_u,
    update_u,
    delete_u,
    block_u,
    unlock_u
};

///actions with one terrain project
enum terrains_action{
    add_t,
    get_t,
    update_t,
    delete_t
};

///actions with terrain projects
enum ter_projs_action{
    get_tpl,                //get terrain project list
};

class Postgres
{
    private:
        std::unique_ptr<UserPostgres> __users;                          //postgres's user management
        std::unique_ptr<TerrainProjectsPostgres> __terrains;            //postgres's terrain management
        Config __config;                                                //configure launch postgres database

        std::shared_ptr<pqxx::connection> __connection;                 //postgres's connection
        int __connect_psql_to_db();

    public:
        Postgres();
        ~Postgres() = default;

        void set_psql_connection(std::shared_ptr<pqxx::connection> &connection);

        int get_count_users();
        int get_count_terrains();

        int do_action_users(const users_action &action, users_t &user);
        int do_action_terrains(const terrains_action &action, terrain_project_t &ter_proj, int &user_id);

        std::pair<int, std::vector<terrain_project_t>>
        do_action_terrain_projects(const ter_projs_action &action, int &user_id);

        bool check_validation(users_t &user);
};

#endif
