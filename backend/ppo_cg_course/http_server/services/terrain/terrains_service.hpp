#ifndef _TERRAINS_SERVICE_HPP_
#define _TERRAINS_SERVICE_HPP_

#include "core/data_access/db_model/base_db_model.hpp"
#include "core/data_access/images/png/png.hpp"
#include "core/scene/scene.h"
#include "core/data_access/terrains/terrains_struct.hpp"
#include "http_server/services/terrain/struct_terrains_service.hpp"
#include "error_codes.h"

class TerrainsService
{
    private:
        std::shared_ptr<DbModel> __dbModel;
        std::shared_ptr<BaseImage> __image;
        Scene __scene;

        int __nUsers, __nTerrains;

        all_scene_info_t __fill_scene_info(dbTerrain_t &terrain, light_t &light);

        void __convertDbToServModel(const dbTerrain_t &dbTer, servTerrain_t &servTer);
        void __convertDbToServModel(const std::vector<dbTerrainProject_t> &dbTer,
                                    std::vector<servTerrainProject_t> &servTer);

    public:
        int get_terrain_projects(const int &userId, std::vector<servTerrainProject_t> &terProjects);
        int get_terrain_params(const int &userId, const int &terId, servTerrain_t &servTer);
        int add_terrain_project(const int &userId, const std::string &terProjName);
        int delete_terrain_project(int &userId, int &terId);
        int get_terrain_project_rating(const int &terId, double &rating);
        int set_terrain_project_rating(int &terId, int &rating);
        bool get_render_png_image(dbTerrain_t &terrain, light_t &light);
        void set_dbModel(std::shared_ptr<DbModel> dbModel);
};

#endif
