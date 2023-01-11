#ifndef _POSTGRES_TERRAINS_H_
#define _POSTGRES_TERRAINS_H_

#include <pqxx/pqxx>
#include <iostream>

#include "core/data_access/terrains/terrains_struct.hpp"
#include "core/heightmap/perlin_noise/perlin_noise_struct.h"
#include "error_codes.h"

class TerrainProjectsPostgres
{
    private:
        std::string __project_name;
        dbTerrain_t __terrain_params;
        int __count_terrain_projs;

        std::shared_ptr<pqxx::connection> __conn_psql;

        void __define_count_terrain_projects();
        std::string __dbName;

    public:
        TerrainProjectsPostgres() = default;
        TerrainProjectsPostgres(std::shared_ptr<pqxx::connection> &conn_psql, const std::string &dbName);

        ~TerrainProjectsPostgres() = default;

        void set_terrain_params(std::string &project_name, dbTerrain_t &terrain_params);
        int get_terrain_projects(const std::string &userName, int &page, std::vector<dbTerrainProject_t> &dbTerProjs);
        int get_terrain_project(const std::string &userName, dbTerrainProject_t &dbTerProj,const std::string &projName="");
        int get_count_terrain_projects();
        int set_terrain_params(const std::string &userName, const std::string &projName, const dbTerrain_t &ter);

        int add_new_terrain_project(const std::string &userName, const std::string &terProjName);
        int get_terrain_params(const std::string &userName, const std::string &projName, dbTerrain_t &ter);
        int get_terrain_params(const std::string &projName, dbTerrain_t &ter);
        int delete_terrain_project(const std::string &userName, const std::string &projName);
        double get_terrain_project_rating(const std::string &projName, double &dbRating);
        int set_terrain_project_rating(const std::string &projName, const std::string &userName);
        int add_project_for_rating(const std::string &userName, const std::string &projName);
        int get_all_rating_projects(const std::string &page, std::vector<dbTerrainProject_t> &dbTerProjs);
};

#endif
