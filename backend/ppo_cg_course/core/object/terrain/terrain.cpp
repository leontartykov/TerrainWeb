#include "terrain.h"
#include "terrain.hpp"
//#include "core/data_access/images/data_access_image_bmp.hpp"
#include "core/invisible/zbuffer/zbuffer.h"
#include "core/geometry/triangle/triangle_3d.hpp"
#include "core/geometry/vector/vector_3d.h"
#include "core/heightmap/perlin_noise/perlin_original.h"
#include "core/transform/transform.h"

/*!
 * \brief Terrain::Terrain
 * the terrain landscape size is a number of triangles in rows and columns
 */
Terrain::Terrain()
{
    _width = _default_height + 1, _height = _default_width + 1;
    this->init_terrain(_width, _height);
}

Terrain::Terrain(int width, int height)
{
    _width = height + 1, _height = width + 1;
    this->init_terrain(_width, _height);
}

void Terrain::init_terrain(int width, int height)
{
    std::vector<Point3D<double>> temp;

    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            temp.push_back(Point3D<double>(0, 0, 0));
        }
        _points.push_back(temp);
        _start_points.push_back(temp);
        _screen_points.push_back(temp);
        temp.clear();
    }

    _meta_config.gain = 0, _meta_config.lacunarity = 0, _meta_config.octaves = 0;
    _meta_config.frequency = 0, _meta_config.seed = 0;
}

Terrain::~Terrain()
{
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _points[i].clear();
            _start_points.clear();
            _screen_points.clear();
        }
    }

    _points.clear();
    _start_points.clear();
    _screen_points.clear();
}

Point3D<double> Terrain::get_point(int index_i, int index_j){
    return _points[index_i][index_j];
}

Point3D<double> Terrain::get_screen_point(int index_i, int index_j){
    return _screen_points[index_i][index_j];
}

int Terrain::get_height(){
    return _height;
}

int Terrain::get_width(){
    return _width;
}

Point3D<double> Terrain::get_center_figure(){
    return _center_terrain_point;
}

void Terrain::set_center_figure(Point3D<double> &point){
    _center_terrain_point.set_point(point.get_x(), point.get_y(), point.get_z());
}

/*!
 * \brief Terrain::remove_invisible_lines
 * \param zbuffer
 * \param light_position
 */
void Terrain::remove_invisible_lines(ZBuffer &zbuffer, Point3D<int> light_position)
{
    plane_coeffs_t plane_coeffs_top, plane_coeffs_bottom;

    //все точки экранных треугольников (верхние, нижние)
    //берем матрицу для того, чтобы поделить на верхнюю часть треугольника
    //и нижнюю
    std::vector<std::vector<rasterised_points_t>> rasterized_points_up, rasterized_points_down;

    //нормали для треугольников (верхние, нижние)
    Vector3D<double> normal_top, normal_down;

    //нормали вершин для каждого треугольника (верхние, нижние)
    Triangle3D<double>top_triangle_normals, bottom_triangle_normals;

    //вершины треугольников (верхний и нижний) в 3д
    Triangle3D<double>triangle_top_3d, triangle_bottom_3d;

    Point3D<int> top_middle_point, bottom_middle_point;
    std::vector<std::vector<QColor>> color_matrix = zbuffer.get_color_matrix();
    std::vector<std::vector<double>> zbuffer_matrix = zbuffer.get_zbuffer_matrix();
    Triangle3D<double> triangle_top, triangle_bottom;

    for (int i = 0; i < _width - 1; i++){
        for (int j = 0; j < _height - 1; j++)
        {
            plane_coeffs_top = find_equation_plane(_points[i][j], _points[i][j+1], _points[i + 1][j + 1]);
            plane_coeffs_bottom = find_equation_plane(_points[i][j], _points[i+1][j], _points[i + 1][j + 1]);

            top_triangle_normals.set_triangle_vector(_shading_normals[i][j], _shading_normals[i][j+1], _shading_normals[i+1][j+1]);
            bottom_triangle_normals.set_triangle_vector(_shading_normals[i][j], _shading_normals[i+1][j], _shading_normals[i+1][j+1]);

            triangle_top.set_triangle(_screen_points[i][j], _screen_points[i][j+1], _screen_points[i + 1][j + 1]);
            triangle_bottom.set_triangle(_screen_points[i][j], _screen_points[i+1][j], _screen_points[i + 1][j + 1]);

            top_middle_point = rasterize_triangle(rasterized_points_up,
                                            triangle_top,
                                            top_triangle_normals, light_position,
                                            color_matrix, plane_coeffs_top);

            bottom_middle_point = rasterize_triangle(rasterized_points_down,
                                                     triangle_bottom,
                                                     bottom_triangle_normals, light_position,
                                                     color_matrix, plane_coeffs_bottom);

            find_depth_pixels(zbuffer_matrix, color_matrix,
                                                 rasterized_points_up, plane_coeffs_top,
                                                 light_position, top_triangle_normals,
                                                 triangle_top_3d);
            find_depth_pixels(zbuffer_matrix, color_matrix,
                                                 rasterized_points_down, plane_coeffs_bottom,
                                                 light_position, bottom_triangle_normals,
                                                 triangle_bottom_3d);

            rasterized_points_up.clear(), rasterized_points_down.clear();
        }
    }

    zbuffer.set_buffer_matrix(zbuffer_matrix);
    zbuffer.set_color_matrix(color_matrix);
}

void Terrain::find_all_normals()
{
    std::vector<Vector3D<int>> row_normals_up_triangles;
    std::vector<Vector3D<int>> row_normals_down_triangles;
    Vector3D<int> normal_up_triangle, normal_down_triangle;
    for (int i = 0; i < _width - 1; i++)
    {
        for (int j = 0; j < _height - 1; j++)
        {
             normal_up_triangle = find_int_normal<int, double>(_points[i][j],
                                                                                    _points[i][j+1],
                                                                                    _points[i+1][j+1]);

             normal_down_triangle= find_int_normal<int, double>(_points[i][j],
                                                                                            _points[i+1][j],
                                                                                            _points[i+1][j+1]);
             row_normals_up_triangles.push_back(normal_up_triangle);
             row_normals_down_triangles.push_back(normal_down_triangle);
        }
        _normals_up_triangles.push_back(row_normals_up_triangles);
        _normals_down_triangles.push_back(row_normals_down_triangles);
        row_normals_up_triangles.clear();
        row_normals_down_triangles.clear();
    }
}

Vector3D<double> Terrain::find_shading_normals(std::vector<Vector3D<int>> &normals, int i, int j)
{
    Vector3D<int> sum_normal;
    Vector3D<double>average_normal;

    int count_normals = normals.size();

    for (int i = 0; i < count_normals; i++){
        sum_normal = sum_normal + normals[i];
    }
    average_normal.set_vector(sum_normal.get_x(), sum_normal.get_y(), sum_normal.get_z());

    average_normal /= count_normals;
    return average_normal;
}

/*!
 * \brief Landscape::find_average_normals_of_each_node
 *  //расчет нормалей в вершинах полигонов
    //случаи:
    //1случай: угловые узлы карты высот (левый верхний и нижний правый - усреднить 2 нормали)
    //2 случай: угловые узлы карты высот (правый верхний и нижний левый - усреднить 1 нормаль)
    //3 случай: все боковые узлы по горизонтали (кроме угловых) - усреднение 3 нормалей
    //4 случай: все боковые узлы по вертикали (кроме угловых) - усреднение 3 нормалей
    //5 случай: все остальные - усреднение 6 нормалей
 */
void Terrain::find_average_normals_of_each_node()
{
    //усредненный вектор
    Vector3D<double> average_vector;

    //все усредненные векторы для каждого ряда узлов
    std::vector<Vector3D<double>> row_shading_normals;

    //векторы нормалей для каждого из случаев
    std::vector<Vector3D<int>> normals;

    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++)
        {
            //1 случай
            if ((i == 0 && j == 0) || (i == _width - 1 && j == _height - 1))
            {
                //qDebug()<< "Случай 1: " << "i = " << i << " j = " << j;
                if (i == 0)
                {
                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else{
                    normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                    normals.push_back(_normals_down_triangles[i - 1][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //2 случай
            else if ((i == 0 && j == _height - 1) || (j == 0 && i == _width- 1))
            {
                //qDebug()<< "Случай 2: " << "i = " << i << " j = " << j;
                if (i == 0){
                    normals.push_back(_normals_up_triangles[i][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else{
                    normals.push_back(_normals_down_triangles[i - 1][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //3 случай
            else if((i == 0 && j > 0 && j < _height - 1) || (i == _width - 1 && j > 0 && j < _height - 1))
            {
                //qDebug()<< "Случай 3: " << "i = " << i << " j = " << j;
                if (i == 0)
                {
                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_up_triangles[i][j - 1]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else
                {
                    normals.push_back(_normals_up_triangles[i - 1][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //4 случай
            else if((j == 0 && i > 0 && i < _width - 1) || (j == _height - 1 && i > 0 && i < _width - 1))
            {
                //qDebug()<< "Случай 4: " << "i = " << i << " j = " << j;
                if (j == 0)
                {
                    normals.push_back(_normals_down_triangles[i-1][j]);
                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else
                {
                    normals.push_back(_normals_up_triangles[i-1][j - 1]);
                    normals.push_back(_normals_up_triangles[i][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j-1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            else
            {
                //qDebug()<< "Случай 5: " << "i = " << i << " j = " << j;
                normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                normals.push_back(_normals_up_triangles[i][j]);
                normals.push_back(_normals_up_triangles[i][j-1]);

                normals.push_back(_normals_down_triangles[i - 1][j - 1]);
                normals.push_back(_normals_down_triangles[i-1][j]);
                normals.push_back(_normals_down_triangles[i][j]);

                average_vector = find_shading_normals(normals, i, j);
                average_vector.normalize();
                row_shading_normals.push_back(average_vector);
            }
            normals.clear();
        }
        _shading_normals.push_back(row_shading_normals);
        row_shading_normals.clear();
    }
}

/*int Terrain::write_to_file_bmp(std::string &path, ZBuffer &zbuffer)
{
    DataAccessFileBMP file_bmp;
    int error = file_bmp.create(path, zbuffer.get_color_matrix());
    return error;
}*/

void Terrain::set_meta_data(meta_data_t &meta_data)
{
    _meta_config.octaves = meta_data.octaves;
    _meta_config.gain = meta_data.gain;
    _meta_config.lacunarity = meta_data.lacunarity;
    _meta_config.seed = meta_data.seed;
    _meta_config.frequency = meta_data.frequency;
}

rotate_t Terrain::get_rotate_angles(){
    return _rotate_landscape_angles;
}

void Terrain::set_rotate_angles(rotate_t &rotate_angles)
{
    _rotate_landscape_angles.angle_x = rotate_angles.angle_x;
    _rotate_landscape_angles.angle_y = rotate_angles.angle_y;
    _rotate_landscape_angles.angle_z = rotate_angles.angle_z;
}

void Terrain::form_terrain()
{
    PerlinNoise map(_meta_config.seed);
    std::cerr << "_width: " << _width << "\n";
    std::cerr << "_height: " << _height << "\n";
    double fx = _width / _meta_config.frequency;
    double fy = _height / _meta_config.frequency;

    for (int x = 0; x < _width; x++){
        for (int y = 0; y < _height; y++){
            _points[x][y].set_point((x+1) * 5, (y+1) * 5, map.accumulatedNoise2D((x)/ fx, y / fy, _meta_config) * 1000);
            _start_points[x][y] = _points[x][y];
        }
    }
}

void Terrain::scale_terrain(double scale)
{
    _scale = scale;
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _points[i][j].set_x(_start_points[i][j].get_x() * scale + (1 - scale) * _center_terrain_point.get_x());
            _points[i][j].set_y(_start_points[i][j].get_y() * scale + (1 - scale) * _center_terrain_point.get_y());
            _points[i][j].set_z(_start_points[i][j].get_z() * scale + (1 - scale) * _center_terrain_point.get_z());
        }
    }
}

void Terrain::transform_points_to_screen()
{
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++){
            transform_3d_into_2d(_screen_points[i][j], _points[i][j]);
            _screen_points[i][j].set_z(_points[i][j].get_z());
        }
    }
}

void Terrain::rotate_terrain(rotate_t &diff_rotate_angles)
{
    Point3D<double> begin_landscape_point, end_landscape_point;

    begin_landscape_point.set_point(_points[0][0].get_x(),
                                                        _points[0][0].get_y(),
                                                        _points[0][0].get_z());
    end_landscape_point.set_point(_points[_points.size() - 1][_points[0].size() - 1].get_x(),
                                                        _points[_points.size() - 1][_points[0].size() - 1].get_y(),
                                                        _points[_points.size() - 1][_points[0].size() - 1].get_z());

    _center_terrain_point.set_point((begin_landscape_point.get_x() + end_landscape_point.get_x()) / 2,
                                            (begin_landscape_point.get_y() + end_landscape_point.get_y()) / 2,
                                            (begin_landscape_point.get_z() + end_landscape_point.get_z()) / 2);

    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            shift_point_by_center(_points[i][j], _center_terrain_point);
            rotate_point(_points[i][j], diff_rotate_angles);
            shift_point_back_by_center(_points[i][j], _center_terrain_point);

            shift_point_by_center(_start_points[i][j], _center_terrain_point);
            rotate_point(_start_points[i][j], diff_rotate_angles);
            shift_point_back_by_center(_start_points[i][j], _center_terrain_point);
        }
    }
}

int Terrain::get_rotate_x(){
    return _rotate_landscape_angles.angle_x;
}

int Terrain::get_rotate_y(){
    return _rotate_landscape_angles.angle_y;
}

int Terrain::get_rotate_z(){
    return _rotate_landscape_angles.angle_z;
}

void Terrain::clear_normals()
{
    int width_landscape = this->get_width(), height_landscape = this->get_height();
    for (int i = 0; i < width_landscape - 1; i++)
    {
        _normals_up_triangles[i].clear();
        _normals_down_triangles[i].clear();
        _shading_normals[i].clear();
    }
    _normals_up_triangles.clear();
    _normals_down_triangles.clear();
    _shading_normals.clear();
}

void Terrain::clear()
{
    for (int i = 0; i < _width; i++){
         _points[i].clear();
         _start_points[i].clear();
         _screen_points[i].clear();
         _shading_normals[i].clear();
    }
    _shading_normals.clear();
    _points.clear();
    _start_points.clear();
    _screen_points.clear();

    _meta_config.gain = 0, _meta_config.lacunarity = 0, _meta_config.octaves = 0;

    for (int i = 0; i < _width - 1; i++)
    {
        _normals_up_triangles[i].clear();
        _normals_down_triangles[i].clear();
    }
    _normals_up_triangles.clear();
    _normals_down_triangles.clear();
}

void Terrain::draw_terrain(std::vector<std::vector<QColor>> &colors, QGraphicsScene *scene, QGraphicsView *view)
{
    QPixmap pixmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    int r = 0, g = 0, b = 0;
    colors[0][0].getRgb(&r, &g, &b);

    for (int i = 0; i < SCREEN_WIDTH; i++){
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            colors[i][j].getRgb(&r, &g, &b);
            if (r != 255 && g != 255 && b != 255){
                painter.setPen(QColor(r, g, b));
                painter.drawLine(i, j, i, j);
            }
        }
    }

    painter.end();
    scene->clear();
    scene->addPixmap(pixmap);
}

void Terrain::change_size(int width, int height){
    _width = height + 1, _height = width + 1;
    this->init_terrain(_width, _height);
}

