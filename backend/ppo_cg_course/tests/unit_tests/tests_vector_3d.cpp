#include <gtest/gtest.h>
#include "core/geometry/vector/vector_3d.hpp"
#include "core/geometry/point/point_3d.hpp"

TEST(test_vector_3d_length_vector, positive)
{
    Vector3D<int> vector(3, 4, 0);
    double length = vector.length();
    double result_ok = 5;
    EXPECT_EQ(result_ok, length);
}

TEST(test_vector_3d_normalize_vector, positive)
{
    Vector3D<double> vector(3, 4, 0);
    vector.normalize();

    double result_x = 0.6, result_y = 0.8, result_z = 0;
    double eps = 0.0001;

    EXPECT_LT(fabs(vector.get_x() - result_x), eps);
    EXPECT_LT(fabs(vector.get_y() - result_y), eps);
    EXPECT_LT(fabs(vector.get_z() - result_z), eps);
}

TEST(test_vector_3d_find_normal, positive)
{
    Point3D<double> point_1(1.0, 2.0, -3.0), point_2(-2.0, 4.0, 1.0), point_3(2.0, -3.0, 2.0);
    Vector3D<double> vector = find_normal<double>(point_1, point_2, point_3);
    int result_x = 30, result_y = 19, result_z = 13;
    EXPECT_EQ(result_x, vector.get_x());
    EXPECT_EQ(result_y, vector.get_y());
    EXPECT_EQ(result_z, vector.get_z());
}

TEST(test_vector_3d_dot_product, positive)
{
    Vector3D<int>vector_1(1, 2, 3),  vector_2(4, 5, 6);
    int result = 32;
    EXPECT_EQ(result, dot_product<int>(vector_1, vector_2));
}
