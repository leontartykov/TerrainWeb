#ifndef _BASE_TERRAIN_SERVICE_
#define _BASE_TERRAIN_SERVICE_

#include <vector>
#include <memory>

#include "core/data_access/terrains/terrains_struct.hpp"
#include "http_server/services/terrain/struct_terrains_service.hpp"
#include "core/data_access/db_model/base_db_model.hpp"
#include "error_codes.h"

class ITerrainService
{
    public:
    virtual ~ITerrainService() {};
    virtual int get_terrain_projects(const std::string &userName, int &page, std::vector<servTerrainProject_t> &terProjects) = 0;
    virtual int get_terrain_params(const std::string &userName, const std::string &projName, servTerrain_t &servTer) = 0;
    virtual int get_terrain_project(const std::string &projName, servTerrainProject_t &project, const std::string &userName="") = 0;
    virtual int add_terrain_project(const std::string &userName, const std::string &terProjName) = 0;
    virtual int save_terrain_params(const std::string &userName, const std::string &projName, const servTerrain_t &servTer) = 0;
    virtual int delete_terrain_project(const std::string &userName, const std::string &projName) = 0;
    virtual int get_terrain_project_rating(const std::string &projName, double &rating) = 0;
    virtual int set_terrain_project_rating(const std::string &projName, const std::string &userName) = 0;
    virtual bool get_render_png_image(dbTerrain_t &terrain, light_t &light) = 0;
    virtual int add_project_for_rating(const std::string &userName, const std::string &projName) = 0;
    virtual int get_all_rating_projects(const std::string &page, std::vector<servTerrainProject_t> &terProjects) = 0;
    virtual int find_rating_project(const std::string &projName, servTerrainProject_t &project) = 0;
    virtual int get_rating_project_values(const std::string &projName, servTerrain_t &project) = 0;

    virtual void set_dbModel(std::shared_ptr<DbModel> dbModel) = 0;
};

#endif
