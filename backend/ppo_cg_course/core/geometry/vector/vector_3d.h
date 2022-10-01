#ifndef _VECTOR_3D_H_
#define _VECTOR_3D_H_

#include "../point/point_3d.h"
#include <cmath>

template <typename T>
class Vector3D
{
    private:
        T _x, _y, _z;
    public:
        Vector3D();
        Vector3D(T x, T y, T z);
        ~Vector3D();

        T get_x();
        T get_y();
        T get_z();
        void set_vector(T x, T y, T z);
        void reset();

        void normalize();

        Vector3D<T> operator / (double length);
        Vector3D<T> &operator /= (double length);
        Vector3D<T> operator+ (Vector3D<T> &vector_2);

        double length();

        void output();
};

template <typename T>
Vector3D<T> find_normal(Point3D<T> point_1, Point3D<T> point_2, Point3D<T> point_3);

template <typename T>
double dot_product(Vector3D<T> &vector_1, Vector3D<T> &vector_2);

#endif
