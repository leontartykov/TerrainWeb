#ifndef _POINT_2D_HPP_
#define _POINT_2D_HPP_

#include "point_2d.h"

template <typename T>
Point2D<T>::Point2D(): _x{0}, _y{0}{
}

template <typename T>
Point2D<T>::Point2D(T x, T y) noexcept: _x(x), _y(y){
}

template <typename T>
Point2D<T>::~Point2D() {
}

template <typename T>
void Point2D<T>::set_point(const T data_x, const T data_y)
{
    _x = data_x;
    _y = data_y;
}

template <typename T>
T Point2D<T>::get_x() const{
    return _x;
}

template <typename T>
T Point2D<T>::get_y() const{
    return _y;
}

template <typename T>
void Point2D<T>::set_x(T x){
    _x = x;
}

template <typename T>
void Point2D<T>::set_y(T y){
    _y = y;
}

template <typename T>
void swap_values(T &value_1, T &value_2)
{
    T temp = value_1;
    value_1 = value_2;
    value_2 = temp;
}

#endif
