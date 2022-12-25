#ifndef _POSTGRES_H_
#define _POSTGRES_H_

#include "core/data_access/db_model/base_db_model.hpp"
#include "core/data_access/db_model/postgres/postgres_data/postgres_users/postgres_user.h"
#include "core/data_access/db_model/postgres/postgres_data/postgres_terrains/postgres_terrains.h"
#include "core/config/config.h"
#include "error_codes.h"

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

        void __convertDbToServModel(const std::vector<dbTerrainProject_t> &dbTer,
                                    std::vector<servTerrainProject_t> &servTer);
        void __convertDbToServModel(const dbTerrain_t &dbTerParams, servTerrain_t &terParams);
        int __nUsers, __nTerrains;

        void __convertServToDbModel(const servUsers_t &servUser, dbUsers_t &dbUser);
        void __convertDbToServModel(const dbUsers_t &dbUser, servUsers_t &servUser);
        void __convertDbToServModel(const dbTerrainProject_t &dbTerProj, servTerrainProject_t &servTerProj);
        void __convertServToDbModel(const servTerrain_t &servTer, dbTerrain_t &dbTer);

    public:
        Postgres();
        virtual ~Postgres() override {}

        virtual int get_user(const int &id, servUsers_t &servUser) override;
        virtual int add_user(const servUsers_t &servUser) override;
        virtual int update_user(const int &id, const servUsers_t &servUser) override;
        virtual int delete_user(const int &id) override;
        virtual int delete_user(const std::string &login) override;
        virtual int block_user(const int &id) override;
        virtual int unlock_user(const int &id) override;

        void set_psql_connection(std::shared_ptr<pqxx::connection> &connection);

        int get_count_users();
        int get_count_terrains();

        virtual int add_new_terrain_project(const std::string &userName, const std::string &terProjName) override;
        virtual int get_terrain_params(const std::string &userName, const std::string &projName, servTerrain_t &terParams) override;
        virtual int get_terrain_projects(const std::string &userName, int &page,
                                         std::vector<servTerrainProject_t> &servTerProjects) override;
        virtual int get_terrain_project(const std::string &projName, servTerrainProject_t &servTerProj, const std::string &userName="----") override;
        virtual int save_terrain_params(const std::string &userName, const std::string &projName, const servTerrain_t &servTer) override;
        virtual int delete_terrain_project(const std::string &userName, const std::string &projName) override;
        virtual int get_terrain_project_rating(const std::string &projName, double &rating) override;
        virtual int set_terrain_project_rating(const std::string &projName, const std::string &userName) override;
        virtual int add_project_for_rating(const std::string &userName, const std::string &projName) override;
        virtual int get_all_rating_projects(const std::string &page, std::vector<servTerrainProject_t> &terProjects) override;

        virtual int login(const std::string &login, const std::string &password, int &uuid) override;
        virtual int login(const std::string &login, const std::string &password) override;
};

#endif
