#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "triangle_3d.h"
#include "../point/point_3d.hpp"

template <typename T>
Triangle3D<T>::Triangle3D()
{
    _triangle[0] = Point3D<T>(0.0, 0.0, 0.0);
    _triangle[1] = Point3D<T>(0.0, 0.0, 0.0);
    _triangle[2] = Point3D<T>(0.0, 0.0, 0.0);
}

template <typename T>
Triangle3D<T>::Triangle3D(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3)
{
    _triangle[0] = point_1;
    _triangle[1] = point_2;
    _triangle[2] = point_3;
}

template <typename T>
Triangle3D<T>::~Triangle3D(){

}

template <typename T>
void Triangle3D<T>::output(){
    std::cout << "[";
    _triangle[0].output_point();
    _triangle[1].output_point();
    _triangle[2].output_point();
    std::cout << "]" << std::endl;
}

template <typename T>
void Triangle3D<T>::set_triangle(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3)
{
    _triangle[0] = point_1;
    _triangle[1] = point_2;
    _triangle[2] = point_3;
}

template <typename T>
void Triangle3D<T>::swap_points(int index_first, int index_second)
{
    Point3D<T> temp_point;
    temp_point = _triangle[index_first - 1];
    _triangle[index_first - 1] = _triangle[index_second - 1];
    _triangle[index_second - 1] = temp_point;
}

template <typename T>
Point3D<T> Triangle3D<T>::operator[] (int index){
    return _triangle[index];
}

template <typename T>
void Triangle3D<T>::set_triangle_vector(Vector3D<T> vector_1,
                                      Vector3D<T> vector_2, Vector3D<T> vector_3)
{
    Point3D<T> point_1, point_2, point_3;
    point_1.set_point(vector_1.get_x(), vector_1.get_y(), vector_1.get_z());
    point_2.set_point(vector_2.get_x(), vector_2.get_y(), vector_2.get_z());
    point_3.set_point(vector_3.get_x(), vector_3.get_y(), vector_3.get_z());

    this->set_triangle(point_1, point_2, point_3);
}

#endif
