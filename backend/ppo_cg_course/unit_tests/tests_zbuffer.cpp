#include <gtest/gtest.h>
#include <QColor>

#include "../core/invisible/zbuffer/zbuffer.hpp"
#include "../core/invisible/zbuffer/zbuffer.h"

TEST(tests_zbuffer_is_background_color, positive)
{
    ZBuffer zbuffer(3,3);

    int index_i = 0, index_j = 0;
    zbuffer.set_color(index_i, index_j, qRgb(128, 128, 128));

    bool result = zbuffer.is_background(index_i, index_j);

    EXPECT_EQ(false, result);
}

TEST(tests_zbuffer_is_equal_colors, positive)
{
    bool result = is_equal_colors(qRgb(128, 128, 128), qRgb(128, 128, 128));
    EXPECT_EQ(true, result);
}

TEST(tests_zbuffer_find_depth_pixel, positive)
{
    int raster_x = 1, raster_y = 2;
    double default_depth = -1000.0;
    plane_coeffs_t plane_coeffs = {.a = 5, .b = -1, .c = 4, .d = 8};
    double result_depth = -2.75;
    double depth = find_depth_pixel(raster_x, raster_y, plane_coeffs, default_depth);
    EXPECT_DOUBLE_EQ(result_depth, depth);
}

TEST(tests_zbuffer_find_depth_pixel, negative)
{
    int raster_x = 1, raster_y = 2;
    double default_depth = -1000.0;
    plane_coeffs_t plane_coeffs = {.a = 5, .b = -1, .c = 0, .d = 8};
    double result_depth = default_depth;
    double depth = find_depth_pixel(raster_x, raster_y, plane_coeffs, default_depth);
    EXPECT_DOUBLE_EQ(result_depth, depth);
}
