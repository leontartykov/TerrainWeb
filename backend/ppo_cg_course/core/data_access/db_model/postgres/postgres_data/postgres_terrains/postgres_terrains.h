#ifndef _POSTGRES_TERRAINS_H_
#define _POSTGRES_TERRAINS_H_

#include <pqxx/pqxx>
#include <iostream>

#include "core/object/terrain/terrain_struct.h"
#include "core/heightmap/perlin_noise/perlin_noise_struct.h"

typedef struct terrain terrain_t;
struct terrain
{
    int width, height;
    double scale;
    meta_data_t meta_config;
    rotate_t rotate_angles;
};

typedef struct terrain_project terrain_project_t;
struct terrain_project
{
    int id;
    std::string name;
    std::string last_edit;
    terrain_t terrain;
};

typedef struct light light_t;
struct light{
    int x, y, z;
};

struct terrain_scene
{
    terrain_t terrain;
    light_t light;
};

class TerrainProjectsPostgres
{
    private:
        std::string __project_name;
        terrain_t __terrain_params;
        int __count_terrain_projs;

        std::shared_ptr<pqxx::connection> __conn_psql;

        void __define_count_terrain_projects();

    public:
        TerrainProjectsPostgres() = default;
        TerrainProjectsPostgres(std::shared_ptr<pqxx::connection> &conn_psql);

        ~TerrainProjectsPostgres() = default;

        void set_terrain_params(std::string &project_name, terrain_t &terrain_params);
        std::pair<int, std::vector<terrain_project_t>> get_terrain_projects(int &user_id);
        int get_count_terrain_projects();

        int add_new_terrain_project(std::string &terProjName, int &user_id);
        int get_terrain_project(terrain_project &ter_proj, int &user_id);
        int delete_terrain_project(int &terId, int &user_id);
        double get_terrain_project_rating(int &terId);
        int set_terrain_project_rating(int &terId, int &rating);
};

#endif
