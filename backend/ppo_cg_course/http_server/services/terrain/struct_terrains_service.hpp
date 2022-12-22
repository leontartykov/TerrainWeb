#ifndef _STRUCT_TERRAIN_SERVICE_HPP_
#define _STRUCT_TERRAIN_SERVICE_HPP_

#include "core/data_access/terrains/terrains_struct.hpp"

typedef struct servTerrain servTerrain_t;
struct servTerrain
{
    int width, height;
    double scale;
    meta_data_t meta_config;
    rotate_t rotate_angles;
};

typedef struct servTerrainProject servTerrainProject_t;
struct servTerrainProject
{
    std::string name;
    std::string last_edit;
    double rating;
    int n_rates;
    bool exhibited;
    servTerrain_t terrain;
};

typedef struct servLight servLight_t;
struct servLight{
    int x, y, z;
};

struct servTerrainScene
{
    servTerrain_t terrain;
    servLight_t light;
};

#endif
