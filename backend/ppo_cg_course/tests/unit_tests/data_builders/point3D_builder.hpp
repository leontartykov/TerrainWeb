#ifndef _POINT3D_BUILDER_HPP_
#define _POINT3D_BUILDER_HPP_

#include <memory>

#include "core/geometry/point/point_3d.h"

template <typename T>
class Point3DBuilder
{
    private:
        Point3D<T> __point = Point3D<T>(0, 0, 0);

    public:
        Point3DBuilder() = default;

        Point3DBuilder(const T &x, const T &y, const T &z){
            __point.set_point(x, y, z);
        }

        std::unique_ptr<Point3DBuilder> WithCoords(const T &x, const T &y, const T &z){
            return std::make_unique<Point3DBuilder>(x, y, z);
        }

        Point3D<T> get(){
            return __point;
        }
};

#endif
