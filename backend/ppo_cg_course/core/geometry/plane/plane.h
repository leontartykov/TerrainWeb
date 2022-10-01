#ifndef _PLANE_H_
#define _PLANE_H_

#include "../point/point_3d.h"

typedef struct plane_coeffs_polygon plane_coeffs_t;
struct plane_coeffs_polygon
{
    int a;
    int b;
    int c;
    double d;
};

plane_coeffs_t find_equation_plane(Point3D<double> point_1,
                       Point3D<double> point_2, Point3D<double>point_3);

#endif
