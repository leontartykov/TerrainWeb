#include "light.h"
#include "../../geometry/vector/vector_3d.hpp"
#include "../../geometry/point/point_3d.hpp"

PointLight::PointLight()
{
    _position.set_point(150, 100, 150);
    _direction.set_vector(0, 0, 0);
}

PointLight::~PointLight() {}

Point3D<int> PointLight::get_position(){
    return _position;
}

void PointLight::set_position(const int x, const int y, const int z){
    _position.set_point(x, y, z);
}
