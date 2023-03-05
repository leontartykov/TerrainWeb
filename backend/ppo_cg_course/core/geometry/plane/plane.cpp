#include "plane.h"
#include "../point/point_3d.hpp"

plane_coeffs_t find_equation_plane(Point3D<double> point_1,
                       Point3D<double> point_2, Point3D<double>point_3)
{
    plane_coeffs_t plane_coeffs;
    int point_1_x = point_1.get_x(), point_1_y = point_1.get_y(), point_1_z = point_1.get_z();
    int point_2_x = point_2.get_x(), point_2_y = point_2.get_y(), point_2_z = point_2.get_z();
    int point_3_x = point_3.get_x(), point_3_y = point_3.get_y(), point_3_z = point_3.get_z();

    int vector_1_x = 0, vector_1_y = 0, vector_1_z = 0;
    int vector_2_x = 0, vector_2_y = 0, vector_2_z = 0;

    plane_coeffs.a = 0, plane_coeffs.b = 0, plane_coeffs.c = 0, plane_coeffs.d = 0;

    vector_1_x = point_2_x - point_1_x;
    vector_1_y = point_2_y - point_1_y;
    vector_1_z = point_2_z - point_1_z;

    vector_2_x = point_3_x - point_1_x;
    vector_2_y = point_3_y - point_1_y;
    vector_2_z = point_3_z - point_1_z;

    plane_coeffs.a = vector_1_y * vector_2_z - vector_1_z * vector_2_y;
    plane_coeffs.b = vector_2_x * vector_1_z - vector_2_z * vector_1_x;
    plane_coeffs.c = vector_1_x * vector_2_y - vector_1_y * vector_2_x;
    plane_coeffs.d = (-plane_coeffs.a *  point_1_x - plane_coeffs.b * point_1_y - plane_coeffs.c * point_1_z);

    return plane_coeffs;
}
