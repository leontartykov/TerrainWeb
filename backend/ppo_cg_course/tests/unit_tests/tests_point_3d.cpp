#include <gtest/gtest.h>
#include "core/geometry/point/point_3d.hpp"

TEST(tests_point_3d_sum_points, positive)
{
    Point3D<int> point_1(1, 1, 2), point_2(2, 2, 3);
    point_1 += point_2;

    int result_x = 3, result_y = 3, result_z = 5;
    EXPECT_EQ(result_x, point_1.get_x());
    EXPECT_EQ(result_y, point_1.get_y());
    EXPECT_EQ(result_z, point_1.get_z());
}

TEST(tests_point_3d_multiply_points, positive)
{
    Point3D<int> point_1(1, 1, 2), point_2(2, 2, 3);
    point_1 *= point_2;

    int result_x = 2, result_y = 2, result_z = 6;
    EXPECT_EQ(result_x, point_1.get_x());
    EXPECT_EQ(result_y, point_1.get_y());
    EXPECT_EQ(result_z, point_1.get_z());
}

TEST(tests_point_3d_substract_points, positive)
{
    Point3D<int> point_1(1, 1, 2), point_2(2, 2, 3);
    point_1 -= point_2;

    int result_x = -1, result_y = -1, result_z = -1;
    EXPECT_EQ(result_x, point_1.get_x());
    EXPECT_EQ(result_y, point_1.get_y());
    EXPECT_EQ(result_z, point_1.get_z());
}
