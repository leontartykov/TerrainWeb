#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../../geometry/point/point_3d.h"
#include "../../geometry/vector/vector_3d.h"

class PointLight
{
    private:
        Point3D<int> _position;
        Vector3D<int> _direction;

    public:
        PointLight();
        ~PointLight();

        Point3D<int> get_position();
        void set_position(int x, int y, int z);
};

#endif
