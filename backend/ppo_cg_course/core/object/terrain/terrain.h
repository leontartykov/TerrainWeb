#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <vector>
#include <QGraphicsScene>
#include <QPainter>

#include "base_terrain.h"
#include "terrain_struct.h"
#include "core/geometry/point/point_3d.h"
#include "core/geometry/vector/vector_3d.h"
#include "core/invisible/zbuffer/zbuffer.h"
#include "core/heightmap/perlin_noise/perlin_original.h"
#include "core/geometry/triangle/triangle_3d.h"

class Terrain
{
    private:
        std::vector<std::vector<Point3D<double>>> _start_points, _points, _screen_points;
        std::vector<std::vector<Vector3D<int>>> _normals_up_triangles, _normals_down_triangles;
        std::vector<std::vector<Vector3D<double>>> _shading_normals;

        const int _default_width = 100, _default_height = 100;
        int _width, _height;
        double _scale;
        Point3D<double> _center_terrain_point;
        meta_data_t _meta_config;
        rotate_t _rotate_landscape_angles;

        void init_terrain(int width, int height);

        template <typename T1, typename T2>
        Vector3D<T1> find_int_normal(Point3D<T2> point_1, Point3D<T2> point_2, Point3D<T2> point_3);

        Vector3D<double> find_shading_normals(std::vector<Vector3D<int>> &normals, int i, int j);

    public:
        Terrain();
        Terrain(int width, int height);
        ~Terrain();

        Point3D<double> get_point(int index_i, int index_j);
        Point3D<double> get_screen_point(int index_i, int index_j);

        int get_height();
        int get_width();

        Point3D<double> get_center_figure();
        void set_center_figure(Point3D<double> &point);

        void remove_invisible_lines(ZBuffer &zbuffer, Point3D<int> light_position);
        void find_all_normals();
        void find_average_normals_of_each_node();
        void form_terrain();

        //int write_to_file_bmp(std::string &path, ZBuffer &zbuffer);
        void set_meta_data(meta_data_t &meta_data);

        rotate_t get_rotate_angles();
        void set_rotate_angles(rotate_t &rotate_angles);
        void scale_terrain(double scale);
        void transform_points_to_screen();
        void rotate_terrain(rotate_t &diff_rotate_angles);

        int get_rotate_x();
        int get_rotate_y();
        int get_rotate_z();

        void clear();
        void clear_normals();

        void draw_terrain(std::vector<std::vector<QColor>> &colors, QGraphicsScene *scene,
                          QGraphicsView *view);

        void change_size(int width, int height);
};

#endif
