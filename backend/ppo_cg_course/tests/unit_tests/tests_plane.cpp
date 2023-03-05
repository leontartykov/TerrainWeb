#include <gtest/gtest.h>

#include "core/geometry/plane/plane.h"
#include "core/geometry/point/point_3d.hpp"
#include "tests/unit_tests/data_builders/point3D_builder.hpp"

TEST(tests_plane_coeffs, positive)
{
    std::unique_ptr<Point3DBuilder<double>> point_1, point_2, point_3;
    plane_coeffs_t plane_coeffs;

    point_1 = Point3DBuilder<double>().WithCoords(1, -3, 5);
    point_2 = Point3DBuilder<double>().WithCoords(-2, 6, 8);
    point_3 = Point3DBuilder<double>().WithCoords(3, 2, -14);

    plane_coeffs = find_equation_plane(point_1->get(),
                                       point_2->get(),
                                       point_3->get());

    EXPECT_EQ(plane_coeffs.a, -186);
    EXPECT_EQ(plane_coeffs.b, -51);
    EXPECT_EQ(plane_coeffs.c, -33);
    EXPECT_EQ(plane_coeffs.d, 198);
}
