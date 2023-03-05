#ifndef _TERRAIN_HPP_
#define _TERRAIN_HPP_

#include "terrain.h"

template <typename T1, typename T2>
Vector3D<T1> Terrain::find_int_normal(Point3D<T2> point_1, Point3D<T2> point_2, Point3D<T2> point_3)
{
    Point3D<T1> int_point_1(point_1.get_x(), point_1.get_y(), point_1.get_z());
    Point3D<T1> int_point_2(point_2.get_x(), point_2.get_y(), point_2.get_z());
    Point3D<T1> int_point_3(point_3.get_x(), point_3.get_y(), point_3.get_z());

    Vector3D<T1> normal = find_normal(int_point_1, int_point_2, int_point_3);
    /*std::cout << "normal:"; normal.output();
    std::cout << std::endl;*/

    return normal;
}

#endif
