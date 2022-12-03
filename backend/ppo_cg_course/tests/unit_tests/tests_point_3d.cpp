#include <gtest/gtest.h>
#include "core/geometry/point/point_3d.hpp"

TEST(tests_point_3d_sum_points, positive)
{
    Point3D<int> point_1(1, 1, 2), point_2(2, 2, 3);

    point_1 += point_2;

    EXPECT_EQ(point_1.get_x(), 3);
    EXPECT_EQ(point_1.get_y(), 3);
    EXPECT_EQ(point_1.get_z(), 5);
}

TEST(tests_point_3d_multiply_points, positive)
{
    Point3D<int> point_1(1, 1, 2), point_2(2, 2, 3);

    point_1 *= point_2;

    EXPECT_EQ(point_1.get_x(), 2);
    EXPECT_EQ(point_1.get_y(), 2);
    EXPECT_EQ(point_1.get_z(), 6);
}

TEST(tests_point_3d_substract_points, positive)
{
    Point3D<int> point_1(1, 1, 2), point_2(2, 2, 3);

    point_1 -= point_2;

    EXPECT_EQ(point_1.get_x(), -1);
    EXPECT_EQ(point_1.get_y(), -1);
    EXPECT_EQ(point_1.get_z(), -1);
}
