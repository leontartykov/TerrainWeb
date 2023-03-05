#ifndef _POINT_3D_H_
#define _POINT_3D_H_

#include <iostream>

template <typename T>
class Point3D
{
private:
    T _x, _y, _z;

public:
    Point3D();
    Point3D(T x, T y, T z) noexcept;
    ~Point3D();

    void set_point(const T data_x, const T data_y, const T data_z);
    T get_x() const;
    T get_y() const;
    T get_z() const;

    void set_x(T x);
    void set_y(T y);
    void set_z(T z);
    Point3D<T> &operator *= (Point3D<T> &point);
    Point3D<T> &operator += (Point3D<T> &point);
    Point3D<T> &operator -= (Point3D<T> &point);

    void output_point();
};

template <typename T>
void swap_points(Point3D<T> &point_1, Point3D<T> &point_2);

#endif
