#ifndef _ZBUFFER_H_
#define _ZBUFFER_H_

#include <vector>
#include <QColor>
#include <limits>
#include "../../geometry/point/point_3d.h"
#include "../../geometry/point/point_3d.hpp"
#include "../../geometry/point/point_2d.hpp"
#include "../../geometry/triangle/triangle_3d.h"
#include "../../geometry/vector/vector_3d.hpp"
#include "../../geometry/plane/plane.h"

#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 900

typedef struct rasterised_points rasterised_points_t;
struct rasterised_points
{
    Point2D<double> point;
    double intensity;
};

class ZBuffer
{
    private:
        std::vector<std::vector<double>> _zbuffer_matrix;
        std::vector<std::vector<QColor>> _color_matrix;

        int _width, _height;
        void _init_zbuffer(int width, int height);

    public:
        ZBuffer() {_init_zbuffer(SCREEN_WIDTH, SCREEN_HEIGHT);}
        ZBuffer(int width, int height) {_init_zbuffer(width, height);}
        ~ZBuffer();

        double get_z_point(int index_i, int index_j) const;
        void set_z_point(int index_i, int index_j, double value);

        std::vector<std::vector<double>> &get_zbuffer_matrix();
        std::vector<std::vector<QColor>> &get_color_matrix();

        int get_width() const;
        int get_height() const;

        bool is_background(int index_i, int index_j);
        bool is_equal_colors(int index_i, int index_j, QColor color);

        void set_color(int index_i, int index_j, QRgb color);
        void reset();

        void set_buffer_matrix(std::vector<std::vector<double>> buffer_matrix);
        void set_color_matrix(std::vector<std::vector<QColor>> color_matrix);

        void convert_color_to_black_and_white();
};

std::vector<std::vector<rasterised_points_t>> create_line_by_int_brezenhem(
                                                         Point3D<int> start_point, Point3D<int> end_point,
                                                        Point3D<double> norm_start, Point3D<double> norm_end,
                                                            Point3D<int> &light_position, plane_coeffs_t &plane_coeffs);

Point3D<int> rasterize_triangle(std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                                    Triangle3D<double>&triangle, Triangle3D<double>&triangle_normals,
                                    Point3D<int> &light_position,
                                    std::vector<std::vector<QColor>> &colors, plane_coeffs_t &plane_coeffs);

void find_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix,
                                            std::vector<std::vector<QColor>> &color_matrix,
                                            std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                                            plane_coeffs_t &plane_coeffs, Point3D<int> &light_position,
                                            Triangle3D<double>&triangle_normals, Triangle3D<double>points_3d);

double find_depth_pixel(int rasterize_x, int rasterize_y,
                                       plane_coeffs_t &plane_coeffs, double zbuffer_value);

bool is_equal_colors(QColor color_1, QColor color_2);

#endif
