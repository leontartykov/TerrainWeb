#ifndef _VECTOR3D_BUILDER_HPP_
#define _VECTOR3D_BUILDER_HPP_

#include <memory>

#include "core/geometry/vector/vector_3d.h"

template <typename T>
class Vector3DBuilder
{
    private:
        Vector3D<T> __vector = Vector3D<T>(0, 0, 0);

    public:
        Vector3DBuilder() = default;

        Vector3DBuilder(const T &x, const T &y, const T &z){
            __vector.set_vector(x, y, z);
        }

        std::unique_ptr<Vector3DBuilder> WithCoords(const T &x, const T &y, const T &z){
            return std::make_unique<Vector3DBuilder>(x, y, z);
        }

        Vector3D<T> get(){
            return __vector;
        }
};

#endif
