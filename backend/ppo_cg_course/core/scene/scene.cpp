#include "scene.h"
#include "core/data_access/images/base_image.hpp"
#include "core/data_access/images/data_access_image_bmp.h"

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

std::pair<std::vector<std::vector<QColor>>, struct scene_window>
        Scene::create_scene(all_scene_info_t &scene_info)
{
    scene_win_t win;
    this->build_scene(scene_info);
    std::vector<std::vector<QColor>> color_matrix = _zbuffer->get_color_matrix();

    int width = color_matrix[0].size(), height = color_matrix.size();
    int min_i = height, min_j = width, max_i = 0, max_j = 0;
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; ++j){
            if (!is_background_color(color_matrix[i][j])){
                if (i < min_i){
                    min_i = i;
                }
                if (i > max_i){
                    max_i = i;
                }

                if (j < min_j){
                    min_j = j;
                }
                if (j > max_j){
                    max_j = j;
                }

            }
        }
    }
    win.min_x = min_j; win.max_x = max_j;
    win.min_y = min_i; win.max_y = max_i;

    //std::cerr << "min_i: " << min_i << " max_i: " << max_i << " min_j: " << min_j << " max_j: " << max_j << "\n";

    return {color_matrix, win};
}

bool Scene::is_background_color(QColor &color){
    if (color.red() == 255 && color.green() == 255 && color.blue() == 255){
        return true;
    }
    return false;
}

void Scene::draw_scene(QGraphicsScene *scene, QGraphicsView *view){
    _terrain->draw_terrain(_zbuffer->get_color_matrix(), scene, view);
}

/*int Scene::export_terrain()
{
    std::shared_ptr<DataAccessFileBMP> image_bmp(new DataAccessFileBMP());

    std::string file_name = "../data/color.bmp";
    int error = image_bmp->create(file_name, _zbuffer->get_color_matrix());
    return error;
}*/
/*
int Scene::load_terrain()
{
    std::shared_ptr<DataAccessFileBMP> image_bmp(new DataAccessFileBMP());
    std::vector<std::vector<QColor>> color_matrix = image_bmp->load("../data/color.bmp");

    if (color_matrix.empty()){
        return -1;
    }

    return 0;
}*/

void Scene::convert_color_to_black_and_white(){
    _zbuffer->convert_color_to_black_and_white();
}
