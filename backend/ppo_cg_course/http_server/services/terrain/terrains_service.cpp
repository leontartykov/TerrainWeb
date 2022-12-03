#include "terrains_service.hpp"

void TerrainsService::set_dbModel(std::shared_ptr<DbModel> dbModel){
    __dbModel = dbModel;
}

int TerrainsService::get_terrain_projects(const int &userId,
                                          std::vector<servTerrainProject_t> &terProjects)
{
    int ret_code = BAD_REQUEST;

    if (userId){
        ret_code = __dbModel->get_terrain_projects(userId, terProjects);
    }

    return ret_code;
}

int TerrainsService::get_terrain_params(const int &userId, const int &terId,
                                        servTerrain_t &servTer){
    int ret_code = BAD_REQUEST;

    if (userId && terId){
        ret_code = __dbModel->get_terrain_params(userId, terId, servTer);
    }

    return ret_code;
}

void TerrainsService::__convertDbToServModel(const dbTerrain_t &dbTer, servTerrain_t &servTer)
{
    servTer.width = dbTer.width;
    servTer.height = dbTer.height;
    servTer.meta_config = dbTer.meta_config;
    servTer.rotate_angles = dbTer.rotate_angles;
    servTer.scale = dbTer.scale;
}

int TerrainsService::add_terrain_project(const int &userId, const std::string &terProjName){
    int ret_code = BAD_REQUEST;
    if (userId && !terProjName.empty()){
        ret_code = __dbModel->add_new_terrain_project(userId, terProjName);
    }

    return ret_code;
}

int TerrainsService::delete_terrain_project(int &userId, int &terId){
    int ret_code = BAD_REQUEST;
    if (userId && terId){
        ret_code = __dbModel->delete_terrain_project(userId, terId);
    }

    return ret_code;
}

int TerrainsService::get_terrain_project_rating(const int &terId, double &rating){
    int ret_code = BAD_REQUEST;

    if (terId){
        ret_code = __dbModel->get_terrain_project_rating(terId, rating);
    }
    return ret_code;
}

int TerrainsService::set_terrain_project_rating(int &terId, int &rating){
    return __dbModel->set_terrain_project_rating(terId, rating);
}

bool TerrainsService::get_render_png_image(dbTerrain_t &terrain, light_t &light)
{
    bool success;
    all_scene_info_t scene_info;
    std::string file_name = "images/fee.png";
    std::vector<std::vector<QColor>> color_matrix;
    struct scene_window win_boards;
    std::shared_ptr<PNGImage> png = std::make_shared<PNGImage>();
    __image = png;

    scene_info = __fill_scene_info(terrain, light);

    auto scene = __scene.create_scene(scene_info);
    color_matrix = scene.first; win_boards = scene.second;
    success = __image->create(file_name, color_matrix, win_boards);
    return success;
}

all_scene_info_t TerrainsService::__fill_scene_info(dbTerrain_t &terrain, light_t &light)
{
    all_scene_info_t scene_info;
    scene_info.scene_meta_data = terrain.meta_config;
    scene_info.scene_point_light_position.set_point(light.x, light.y, light.z);
    scene_info.scene_rotate_terrain_angles = terrain.rotate_angles;
    scene_info.scene_terrain_scale = terrain.scale;

    return scene_info;
}
