#include <gtest/gtest.h>

#include "core/geometry/plane/plane.h"
#include "core/geometry/point/point_3d.hpp"

TEST(tests_plane_coeffs, positive)
{
    Point3D<double> point_1(1.0, -3.0, 5.0), point_2(-2.0, 6.0, 8.0), point_3(3.0, 2.0, -14.0);
    plane_coeffs_t plane_coeffs_result = {.a = -186, .b = -51, .c = -33, .d = 198};

    plane_coeffs_t plane_coeffs = find_equation_plane(point_1, point_2, point_3);

    EXPECT_EQ(plane_coeffs.a, plane_coeffs_result.a);
    EXPECT_EQ(plane_coeffs.b, plane_coeffs_result.b);
    EXPECT_EQ(plane_coeffs.c, plane_coeffs_result.c);
    EXPECT_EQ(plane_coeffs.d, plane_coeffs_result.d);
}
