#ifndef _POSTGRES_TERRAINS_H_
#define _POSTGRES_TERRAINS_H_

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
        terrain_t __terrain_params;

    public:
        TerrainProjectsPostgres() = default;
        ~TerrainProjectsPostgres() = default;
        void set_terrain_params(terrain_t &terrain_params);
};

#endif
