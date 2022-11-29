#ifndef TERRAINS_STRUCT_HPP
#define TERRAINS_STRUCT_HPP

#include <iostream>

#include "core/object/terrain/terrain_struct.h"
#include "core/heightmap/perlin_noise/perlin_noise_struct.h"

typedef struct dbTerrain dbTerrain_t;
struct dbTerrain
{
    int width, height;
    double scale;
    meta_data_t meta_config;
    rotate_t rotate_angles;
};

typedef struct dbTerrainProject dbTerrainProject_t;
struct dbTerrainProject
{
    int id;
    std::string name;
    std::string last_edit;
    dbTerrain_t terrain;
};

typedef struct light light_t;
struct light{
    int x, y, z;
};

struct terrainScene
{
    dbTerrain_t terrain;
    light_t light;
};

#endif // TERRAINS_STRUCT_HPP
