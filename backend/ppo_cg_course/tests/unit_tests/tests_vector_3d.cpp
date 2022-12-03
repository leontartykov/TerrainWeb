#include <gtest/gtest.h>
#include "core/geometry/vector/vector_3d.hpp"
#include "core/geometry/point/point_3d.hpp"
#include "tests/unit_tests/data_builders/point3D_builder.hpp"
#include "tests/unit_tests/data_builders/vector3D_builder.hpp"

TEST(test_vector_3d_length_vector, positive)
{
    std::unique_ptr<Vector3DBuilder<int>> vector;
    double length;

    vector = Vector3DBuilder<int>().WithCoords(3, 4, 0);
    length = vector->get().length();

    EXPECT_EQ(length, 5);
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
    std::unique_ptr<Point3DBuilder<double>> point_1, point_2, point_3;
    Vector3D<double> vector;

    point_1 = Point3DBuilder<double>().WithCoords(1, 2, -3);
    point_2 = Point3DBuilder<double>().WithCoords(-2, 4, 1);
    point_3 = Point3DBuilder<double>().WithCoords(2, -3, 2);

    vector = find_normal<double>(point_1->get(), point_2->get(), point_3->get());

    EXPECT_EQ(vector.get_x(), 30);
    EXPECT_EQ(vector.get_y(), 19);
    EXPECT_EQ(vector.get_z(), 13);
}

TEST(test_vector_3d_dot_product, positive)
{
    Vector3D<int> vector_11, vector_12;
    std::unique_ptr<Vector3DBuilder<int>> vector_1, vector_2;

    vector_1 = Vector3DBuilder<int>().WithCoords(1, 2, 3);
    vector_2 = Vector3DBuilder<int>().WithCoords(4, 5, 6);

    vector_11 = vector_1->get();
    vector_12 = vector_2->get();

    EXPECT_EQ(dot_product<int>(vector_11, vector_12), 32);
}
