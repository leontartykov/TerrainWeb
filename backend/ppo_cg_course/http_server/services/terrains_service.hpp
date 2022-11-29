#ifndef _TERRAINS_SERVICE_HPP_
#define _TERRAINS_SERVICE_HPP_

#include "core/data_access/db_model/postgres/postgres_init/postgres.h"
#include "core/data_access/images/png/png.hpp"
#include "core/scene/scene.h"

class TerrainsService
{
    private:
        Postgres __postgres;
        PNGImage __png_image;
        Scene __scene;

        all_scene_info_t __fill_scene_info(terrain_t &terrain, light_t &light);

    public:
        std::pair<int, std::vector<terrain_project_t>> get_terrain_projects(int &userId);
        int get_one_ter_proj(terrain_project &ter_proj, int &userId);

        int add_terrain_project(std::string &terProjName, int &userId);
        int delete_terrain_project(int &userId, int &terId);
        double get_terrain_project_rating(int &terId);
        int set_terrain_project_rating(int &terId, int &rating);
        bool get_render_png_image(terrain_t &terrain, light_t &light);
};

#endif
