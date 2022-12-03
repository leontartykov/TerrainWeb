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

    public:
        TerrainProjectsPostgres() = default;
        TerrainProjectsPostgres(std::shared_ptr<pqxx::connection> &conn_psql);

        ~TerrainProjectsPostgres() = default;

        void set_terrain_params(std::string &project_name, dbTerrain_t &terrain_params);
        int get_terrain_projects(const int &user_id, std::vector<dbTerrainProject_t> &dbTerProjs);
        int get_count_terrain_projects();

        int add_new_terrain_project(const int &user_id, const std::string &terProjName);
        int get_terrain_params(const int &user_id, const int &terId, dbTerrain_t &ter);
        int delete_terrain_project(const int &userId, const int &terId);
        double get_terrain_project_rating(const int &terId, double &dbRating);
        int set_terrain_project_rating(const int &terId, const int &rating);
};

#endif
