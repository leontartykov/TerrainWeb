#ifndef _POINT_3D_HPP_
#define _POINT_3D_HPP_

#include "point_3d.h"

template <typename T>
Point3D<T>::Point3D(): _x{0}, _y{0}, _z{0} {
}

template <typename T>
Point3D<T>::Point3D(T x, T y, T z) noexcept: _x(x), _y(y), _z(z){
}

template <typename T>
Point3D<T>::~Point3D() {
}

template <typename T>
void Point3D<T>::set_point(const T data_x, const T data_y, const T data_z)
{
    _x = data_x;
    _y = data_y;
    _z = data_z;
}

template <typename T>
T Point3D<T>::get_x() const{
    return _x;
}

template <typename T>
T Point3D<T>::get_y() const{
    return _y;
}

template <typename T>
T Point3D<T>::get_z() const{
    return _z;
}

template <typename T>
void Point3D<T>::set_x(T x){
    _x = x;
}

template <typename T>
void Point3D<T>::set_y(T y){
    _y = y;
}

template <typename T>
void Point3D<T>::set_z(T z){
    _z = z;
}

template <typename T>
void Point3D<T>::output_point(){
    std::cout << "(" << _x << ", " << _y << ", " << _z << ")";
}

template <typename T>
Point3D<T> &Point3D<T>::operator *= (Point3D<T> &point)
{
    _x *= point.get_x();
    _y *= point.get_y();
    _z *= point.get_z();
    return *this;
}

template <typename T>
Point3D<T> &Point3D<T>::operator += (Point3D<T> &point)
{
    _x += point.get_x();
    _y += point.get_y();
    _z += point.get_z();
    return *this;
}

template <typename T>
Point3D<T> &Point3D<T>::operator -= (Point3D<T> &point)
{
    _x -= point.get_x();
    _y -= point.get_y();
    _z -= point.get_z();
    return *this;
}

template <typename T>
void swap_points(Point3D<T> &point_1, Point3D<T> &point_2)
{
    Point3D<T> temp_point;

    temp_point.set_point(point_1.get_x(), point_1.get_y(), 0);
    point_1.set_point(point_2.get_x(), point_2.get_y(), 0);
    point_2.set_point(temp_point.get_x(), temp_point.get_y(), 0);
}

#endif
