#ifndef _POSTGRES_TERRAINS_H_
#define _POSTGRES_TERRAINS_H_

#include <pqxx/pqxx>

#include "../../../object/terrain/terrain_struct.h"
#include "../../../heightmap/perlin_noise/perlin_noise_struct.h"

typedef struct terrain terrain_t;
struct terrain
{
    int width, height;
    double scale;
    meta_data_t meta_config;
    rotate_t rotate_angles;
};

class TerrainProjectsPostgres
{
    private:
        std::string __project_name;
        terrain_t __terrain_params;

        std::shared_ptr<pqxx::connection> __conn_psql;

    public:
        TerrainProjectsPostgres() = default;
        ~TerrainProjectsPostgres() = default;

        void set_psql_connection(std::shared_ptr<pqxx::connection> &conn_psql);

        void set_terrain_params(std::string &project_name, terrain_t &terrain_params);
        void get_project_terrain();
};

#endif
