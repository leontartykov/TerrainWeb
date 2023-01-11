#ifndef _SCENE_STRUCT_H_
#define _SCENE_STRUCT_H_

#include "../object/terrain/terrain_struct.h"
#include "../heightmap/perlin_noise/perlin_noise_struct.h"
#include "../geometry/point/point_3d.h"

typedef struct terSize terSize_t;
struct terSize{
    int width;
    int height;
};

typedef struct all_scene_info all_scene_info_t;
struct all_scene_info
{
    terSize_t terSize;
    meta_data_t scene_meta_data;
    rotate_t scene_rotate_terrain_angles;
    double scene_terrain_scale;
    Point3D<int> scene_point_light_position;
};

#endif
