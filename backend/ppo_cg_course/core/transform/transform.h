#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <array>
#include <vector>
#include <cmath>
#include "../geometry/point/point_3d.h"
#include "../object/terrain/terrain_struct.h"

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 900

void transform_3d_into_2d(Point3D<double> &screen_points, Point3D<double> &point);

void shift_point_by_center(Point3D<double> &point, Point3D<double> &center_figure_point);
void shift_point_back_by_center(Point3D<double> &point, Point3D<double> &center_figure_point);

void rotate_point(Point3D<double> &point, rotate_t &rotate_angles);
void rotate_x(Point3D<double> &point, double angle_x);
void rotate_y(Point3D<double> &point,  double angle_y);
void rotate_z(Point3D<double> &point,  double angle_z);

void swap(int &value_1, int &value_2);

#endif
