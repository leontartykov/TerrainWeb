#include "scene.h"
#include "../data_access/data_access_image/data_access_image_base.h"
#include "../data_access/data_access_image/data_access_image_bmp.h"

Scene::Scene(){
    _terrain = new Terrain();
    _zbuffer = new ZBuffer();
}

Scene::~Scene(){
    delete[] _terrain;
    delete[] _zbuffer;
}

void Scene::set_terrain(Terrain *terrain){
    _terrain = terrain;
}

void Scene::set_zbuffer(ZBuffer *zbuffer){
    _zbuffer = zbuffer;
}

Terrain *Scene::get_terrain(){
    return _terrain;
}

ZBuffer *Scene::get_zbuffer(){
    return _zbuffer;
}

void Scene::build_scene(all_scene_info_t &scene_info)
{
    _terrain->set_meta_data(scene_info.scene_meta_data);
    _terrain->set_rotate_angles(scene_info.scene_rotate_terrain_angles);
    _terrain->form_terrain();
    _terrain->find_all_normals();
    _terrain->find_average_normals_of_each_node();

    _terrain->rotate_terrain(scene_info.scene_rotate_terrain_angles);
    _terrain->scale_terrain(scene_info.scene_terrain_scale);
    _terrain->transform_points_to_screen();
    _terrain->remove_invisible_lines(*_zbuffer, scene_info.scene_point_light_position);
}

void Scene::draw_scene(QGraphicsScene *scene, QGraphicsView *view){
    _terrain->draw_terrain(_zbuffer->get_color_matrix(), scene, view);
}

int Scene::export_terrain()
{
    std::shared_ptr<DataAccessFileBMP> image_bmp(new DataAccessFileBMP());
    //std::shared_ptr<BaseDataAccessImage> base_image = image_bmp;

    int error = image_bmp->create("../data/color.bmp", _zbuffer->get_color_matrix());
    return error;
}

int Scene::load_terrain()
{
    std::shared_ptr<DataAccessFileBMP> image_bmp(new DataAccessFileBMP());
    std::vector<std::vector<QColor>> color_matrix = image_bmp->load("../data/color.bmp");

    if (color_matrix.empty()){
        return -1;
    }

    return 0;
}

void Scene::convert_color_to_black_and_white(){
    _zbuffer->convert_color_to_black_and_white();
}
