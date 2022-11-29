#include "terrains_service.hpp"

std::pair<int, std::vector<dbTerrainProject_t>>
    TerrainsService::get_terrain_projects(int &userId)
{
    return __postgres.get_terrain_projects(userId);
}

int TerrainsService::get_one_ter_proj(dbTerrainProject_t &ter_proj, int &userId){
    return __postgres.get_terrain_project(ter_proj, userId);
}

int TerrainsService::add_terrain_project(std::string &terProjName, int &userId){
    return __postgres.add_new_terrain_project(terProjName, userId);
}

int TerrainsService::delete_terrain_project(int &userId, int &terId){
    return __postgres.delete_terrain_project(terId, userId);
}

double TerrainsService::get_terrain_project_rating(int &terId){
    return __postgres.get_terrain_project_rating(terId);
}

int TerrainsService::set_terrain_project_rating(int &terId, int &rating){
    return __postgres.set_terrain_project_rating(terId, rating);
}

bool TerrainsService::get_render_png_image(dbTerrain_t &terrain, light_t &light)
{
    bool success;
    all_scene_info_t scene_info;
    std::string file_name = "images/fee.png";
    std::vector<std::vector<QColor>> color_matrix;
    struct scene_window win_boards;

    scene_info = __fill_scene_info(terrain, light);

    auto scene = __scene.create_scene(scene_info);
    color_matrix = scene.first; win_boards = scene.second;
    success = __png_image.create(file_name, color_matrix, win_boards);
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
