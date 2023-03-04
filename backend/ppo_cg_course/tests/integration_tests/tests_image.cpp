#include <gtest/gtest.h>

#include "tests/unit_tests/data_builders/terrain_builder.hpp"
#include "http_server/services/terrain/terrains_service.hpp"
#include "core/data_access/images/png/png.hpp"

TEST(test_compare_get_terrain_picture_with_params, positive)
{
    std::unique_ptr<TerrainBuilder> scene_info;
    std::unique_ptr<TerrainsService> terService;
    PNGImage png;
    dbTerrain_t terParams;
    light_t light;
    std::vector<std::vector<QColor>> color_buffer;
    int success;

    terService = std::make_unique<TerrainsService>();
    scene_info = std::make_unique<TerrainBuilder>()->BuildDefault();
    terParams = scene_info->get_scene_params().first;
    light = scene_info->get_scene_params().second;

    //Read test image
    auto test_image = scene_info->get_test_image();

    //Render image
    success = terService->get_render_png_image(terParams, light);
    ASSERT_EQ(success, true);

    //Load rendered image
    png.load("../images/test_image.png", color_buffer);

    //Compare images
    for (int i = 0; i < color_buffer.size(); ++i){
        for (int j = 0; j < color_buffer[0].size(); ++j){
            ASSERT_EQ(color_buffer[i][j].red(), test_image[i][j].red());
            ASSERT_EQ(color_buffer[i][j].green(), test_image[i][j].green());
            ASSERT_EQ(color_buffer[i][j].blue(), test_image[i][j].blue());
        }
    }
}
