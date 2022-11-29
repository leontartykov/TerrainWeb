#ifndef _POSTGRES_H_
#define _POSTGRES_H_

#include "core/data_access/db_model/postgres/postgres_data/postgres_users/postgres_user.h"
#include "core/data_access/db_model/postgres/postgres_data/postgres_terrains/postgres_terrains.h"
#include "core/config/config.h"
#include "core/data_access/db_model/base_db_model.hpp"

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

class Postgres: public DbModel
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

        virtual int get_user(int &id, users_t &user) override;
        virtual int add_user(users_t &user) override;
        virtual int update_user(int &id, users_t &user) override;
        virtual int delete_user(int &id) override;
        virtual int block_user(int &id) override;
        virtual int unlock_user(int &id) override;

        void set_psql_connection(std::shared_ptr<pqxx::connection> &connection);

        int get_count_users();
        int get_count_terrains();

        bool check_validation(users_t &user);

        virtual int add_new_terrain_project(std::string &terProjName, int &userId) override;
        virtual int get_terrain_project(terrain_project &terProj, int &userId) override;
        virtual std::pair<int, std::vector<terrain_project_t> > get_terrain_projects(int &userId) override;
        virtual int delete_terrain_project(int &terId, int &userId) override;
        virtual double get_terrain_project_rating(int &terId) override;
        virtual int set_terrain_project_rating(int &terId, int &rating) override;
};

#endif
