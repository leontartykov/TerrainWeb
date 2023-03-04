#ifndef TERRAIN_BUILDER_HPP
#define TERRAIN_BUILDER_HPP

#include <memory>
#include <array>
#include <fstream>
#include <QColor>
#include "core/data_access/terrains/terrains_struct.hpp"

class TerrainBuilder
{
    private:
        dbTerrain_t __terParams;
        light_t __light;
        static constexpr int __rows = 174, __columns = 630;
        std::array<std::array<QColor, __columns>, __rows> __image_color_codes;
        std::ifstream __test_image_file;


    public:
        TerrainBuilder() = default;
        TerrainBuilder(dbTerrain_t &terParams, light_t &light){
            __terParams = terParams;
            __light = light;

            __test_image_file.open("../ppo_cg_course/tests/test_data/test_image.txt", std::ios::in);
            for (int i = 0, red, green, blue; i < __rows; ++i){
                for (int j = 0; j < __columns; ++j){
                    __test_image_file >> red;
                    __image_color_codes[i][j].setRed(red);
                    __test_image_file >> green;
                    __image_color_codes[i][j].setGreen(green);
                    __test_image_file >> blue;
                    __image_color_codes[i][j].setBlue(blue);
                }
            }
        }

        std::unique_ptr<TerrainBuilder>BuildDefault(){
            dbTerrain_t terParams;
            light_t light;

            terParams.meta_config.frequency = 1;
            terParams.meta_config.gain = 0.35;
            terParams.meta_config.lacunarity = 2.3;
            terParams.meta_config.octaves = 6;
            terParams.meta_config.seed = 28;
            terParams.rotate_angles.angle_x = 50;
            terParams.rotate_angles.angle_y = 0;
            terParams.rotate_angles.angle_z = 0;
            terParams.scale = 1;
            terParams.width = 50;
            terParams.height = 51;

            light.x = 100; light.y = 100; light.z = 100;

            return std::make_unique<TerrainBuilder>(terParams, light);
        }

        std::pair<dbTerrain_t, light_t> get_scene_params(){
            return {__terParams, __light};
        }

        std::array<std::array<QColor, __columns>, __rows> get_test_image(){
            return __image_color_codes;
        }
};

#endif // TERRAIN_BUILDER_HPP
