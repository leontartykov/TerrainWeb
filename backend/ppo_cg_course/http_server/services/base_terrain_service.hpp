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
    virtual int get_terrain_projects(const int &userId, int &page, std::vector<servTerrainProject_t> &terProjects) = 0;
    virtual int get_terrain_params(const int &userId, const int &terId, servTerrain_t &servTer) = 0;
    virtual int get_terrain_project(const int &userId, const std::string &projName, servTerrainProject_t &project) = 0;
    virtual int add_terrain_project(const int &userId, const std::string &terProjName) = 0;
    virtual int delete_terrain_project(int &userId, const std::string &projName) = 0;
    virtual int get_terrain_project_rating(const int &terId, double &rating) = 0;
    virtual int set_terrain_project_rating(int &terId, int &rating) = 0;
    virtual bool get_render_png_image(dbTerrain_t &terrain, light_t &light) = 0;
    virtual void set_dbModel(std::shared_ptr<DbModel> dbModel) = 0;
};

#endif
