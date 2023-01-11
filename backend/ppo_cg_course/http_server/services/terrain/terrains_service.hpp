#ifndef _TERRAINS_SERVICE_HPP_
#define _TERRAINS_SERVICE_HPP_

#include <memory>

#include "http_server/services/base_terrain_service.hpp"
#include "core/data_access/images/png/png.hpp"
#include "core/scene/base_scene.hpp"

class TerrainsService: public ITerrainService
{
    private:
        std::shared_ptr<DbModel> __dbModel;
        std::shared_ptr<BaseImage> __image;
        std::shared_ptr<IScene> __scene;

        int __nUsers, __nTerrains;

        all_scene_info_t __fill_scene_info(dbTerrain_t &terrain, light_t &light);

        void __convertDbToServModel(const dbTerrain_t &dbTer, servTerrain_t &servTer);
        void __convertDbToServModel(const std::vector<dbTerrainProject_t> &dbTer,
                                    std::vector<servTerrainProject_t> &servTer);

    public:
        TerrainsService();

        virtual int get_terrain_projects(const std::string &userName, int &page, std::vector<servTerrainProject_t> &terProjects) override;
        virtual int get_terrain_params(const std::string &userName, const std::string &projName, servTerrain_t &servTer) override;
        virtual int add_terrain_project(const std::string &userName, const std::string &terProjName) override ;
        virtual int get_terrain_project(const std::string &projName, servTerrainProject_t &project, const std::string &userName="") override;
        virtual int save_terrain_params(const std::string &userName, const std::string &projName, const servTerrain_t &servTer) override;
        virtual int delete_terrain_project(const std::string &userName, const std::string &projName) override;
        virtual int get_terrain_project_rating(const std::string &projName, double &rating) override;
        virtual int set_terrain_project_rating(const std::string &projName, const std::string &userName) override;
        virtual bool get_render_png_image(dbTerrain_t &terrain, light_t &light) override;
        virtual int add_project_for_rating(const std::string &userName, const std::string &projName) override;
        virtual int get_all_rating_projects(const std::string &page, std::vector<servTerrainProject_t> &terProjects) override;
        virtual int find_rating_project(const std::string &projName, servTerrainProject_t &project) override;
        virtual int get_rating_project_values(const std::string &projName, servTerrain_t &project) override;

        virtual void set_dbModel(std::shared_ptr<DbModel> dbModel) override;
};

#endif
