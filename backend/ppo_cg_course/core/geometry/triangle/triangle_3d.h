#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <array>
#include <vector>

#include "../point/point_3d.h"
#include "../vector/vector_3d.h"

template <typename T>
class Triangle3D
{
private:
    std::array<Point3D<T>, 3> _triangle;
    std::array<Vector3D<T>, 3> _normals;
public:
    Triangle3D();
    Triangle3D(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3);
    ~Triangle3D();

    void set_triangle(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3);
    void swap_points(int index_first, int index_second);

    Point3D<T> operator[] (int index);

    void set_triangle_vector(Vector3D<T> vector_1, Vector3D<T> vector_2,
                                           Vector3D<T> vector_3);

    void output();
};

#endif
