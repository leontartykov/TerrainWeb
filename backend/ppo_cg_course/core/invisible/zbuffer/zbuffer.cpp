#include "zbuffer.h"
#include "../../geometry/triangle/triangle_3d.hpp"

/*!
 * \brief sort_triangle_points_inc -- define min, middle, max points
 * \param point_1
 * \param point_2
 * \param point_3
 */
std::array<Point3D<int>, 3> define_points_sort_inc(Point3D<double> point_1, Point3D<double> point_2,
                                              Point3D<double> point_3, Triangle3D<double>triangle_normals)
{
    std::array<Point3D<int>, 3> points;
    Point3D<int> point_triangle_1, point_triangle_2, point_triangle_3;
    point_triangle_1.set_point(point_1.get_x(), point_1.get_y(), point_1.get_z());
    point_triangle_2.set_point(point_2.get_x(), point_2.get_y(), point_2.get_z());
    point_triangle_3.set_point(point_3.get_x(), point_3.get_y(), point_3.get_z());

    Point3D<int> min_point, max_point, middle_point;
    if (point_triangle_2.get_y() < point_triangle_1.get_y()){
        swap_points(point_triangle_1, point_triangle_2);
        triangle_normals.swap_points(1, 2);
    }

    if (point_triangle_3.get_y() < point_triangle_1.get_y()){
        swap_points<int>(point_triangle_1, point_triangle_3);
        triangle_normals.swap_points(1, 3);
    }

    if (point_triangle_2.get_y() > point_triangle_3.get_y()){
        swap_points<int>(point_triangle_2, point_triangle_3);
        triangle_normals.swap_points(2, 3);
    }

    min_point.set_point(point_triangle_1.get_x(), point_triangle_1.get_y(), 0);
    middle_point.set_point(point_triangle_2.get_x(), point_triangle_2.get_y(), 0);
    max_point.set_point(point_triangle_3.get_x(), point_triangle_3.get_y(), 0);

    points[0] = min_point, points[1] = middle_point, points[2] = max_point;
    return points;
}

int sign(int x)
{
    int value = 0;
    if (x > 0)
        value = 1;
    else if (x == 0)
        value = 0;
    else
        value = -1;

    return value;
}

/*!
 * \brief create_line_by_int_brezenhem
 * \param start_point
 * \param end_point
 * \param norm_start
 * \param norm_end
 * \param light_position
 * \param plane_coeffs
 * \return rasterized points (cordinates)
 */
std::vector<std::vector<rasterised_points_t>> create_line_by_int_brezenhem(
                                                         Point3D<int> start_point, Point3D<int> end_point,
                                                        Point3D<double> norm_start, Point3D<double> norm_end,
                                                            Point3D<int> &light_position, plane_coeffs_t &plane_coeffs)
{
    std::vector<std::vector<rasterised_points_t>> edge;
    std::vector<rasterised_points_t> edge_board;
    Vector3D<double>edge_current, edge_all;
    Vector3D<double> light_direction;
    rasterised_points_t point;
    Vector3D<double> normal_start, normal_end;
    normal_start.set_vector(norm_start.get_x(), norm_start.get_y(), norm_start.get_z());
    normal_end.set_vector(norm_end.get_x(), norm_end.get_y(), norm_end.get_z());

    int flag_exchange = 0;
    int x_start = start_point.get_x(), y_start = start_point.get_y();
    int x_end = end_point.get_x(), y_end = end_point.get_y();

    int dx = x_end - x_start, dy = y_end - y_start;
    int sx = sign(dx), sy = sign(dy);
    dx = abs(dx), dy = abs(dy);

    if (dx > dy)
        flag_exchange = 0;
    else
    {
        flag_exchange = 1;
        swap_values(dx, dy);
    }

    double f = 2 * dy - dx;
    int x_temp = x_start, y_temp = y_start;
    int i = 0;
    bool is_add_points = false;
    double z = 0, x_3d = 0, y_3d = 0;
    double Istart = 0, Iend = 0, intensity = 0, t = 0;

    //длина векторов V1U и V1V2
    double length_x_xstart = 0, length_xstart_xend = 0;
    edge_all.set_vector(x_end - x_start, y_end - y_start, 0);

    //длина вектора Vstart Vend
    length_xstart_xend = edge_all.length();

    x_3d = (int)((x_start - SCREEN_WIDTH / 4) * (z + 1000)/1000);
    y_3d = (int)((y_start - SCREEN_HEIGHT / 4) * (z + 1000)/1000);
    light_direction.set_vector(light_position.get_x() - x_3d,
                                             light_position.get_y() - y_3d,
                                             light_position.get_z() - start_point.get_z());
    light_direction.normalize();

    Istart = std::max(dot_product<double>(normal_start, light_direction), 0.0);

    x_3d = ((x_end - SCREEN_WIDTH / 4) * (z + 1000)/1000);
    y_3d = ((y_end - SCREEN_HEIGHT / 4) * (z + 1000)/1000);
    light_direction.set_vector(light_position.get_x() - x_3d,
                                             light_position.get_y() - y_3d,
                                             light_position.get_z() - end_point.get_z());
    light_direction.normalize();

    Iend = std::max(dot_product<double>(normal_end, light_direction), 0.0);

    while (i <= dx)
    {
        if (is_add_points == true){
            edge.push_back(edge_board);
            edge_board.clear();
            is_add_points = false;
        }

        if (i == 0){
            intensity = Istart;
        }
        else{
            edge_current.set_vector(x_temp - x_start, y_temp - y_start, 0);
            length_x_xstart = edge_current.length();

            t = length_x_xstart / length_xstart_xend;
            intensity = (1 - t) * Istart + t * Iend;
        }

        point.point = Point2D<double>(x_temp, y_temp);
        point.intensity = intensity;
        edge_board.push_back(point);

        if (f >= 0){
            if (flag_exchange == 1){
                x_temp += sx;
            }
            else
            {
                y_temp += sy;
                is_add_points = true;
            }
            f -= 2 * dx;
        }

        if (f < 0){
            if (flag_exchange == 1)
            {
                y_temp += sy;
                is_add_points = true;
            }
            else{
                x_temp += sx;
            }
        }

        f += 2 * dy;
        i++;
    }

    edge.push_back(edge_board);
    edge_board.clear();

    return edge;
}

void swap_rasterised_points(rasterised_points_t &value_1, rasterised_points_t &value_2){
    rasterised_points_t temp_value = value_1;
    value_1 = value_2;
    value_2 = temp_value;
}

/*!
 * \brief find_rasterize_points_right_bottom
 * \param rasterized_points
 * \param edge_1 -- array of pixel coordinates
 * \param edge_2 -- array of pixel coordinates
 * find rasterized (2d coordinate) pixels of bottom part (in screen) triangle
 * which middle point (x coordinate) locates right than max
 */
void find_rasterize_points_right_bottom(
        std::vector<std::vector<rasterised_points_t>> &rasterized_points,
        std::vector<std::vector<rasterised_points_t>> &edge_2,
        std::vector<std::vector<rasterised_points_t>> &edge_3)
{
    double t = 0, intensity = 0;
    std::vector<rasterised_points_t> temp_points;
    rasterised_points_t point;
    int edge_2_i_size;
    int edge_2_size = edge_2.size(),
         edge_3_size = edge_3.size();

    for (int i = edge_3_size - 1, j = 0; i >=0; i--, j++)
    {
        edge_2_i_size = edge_2[edge_2_size - 1 - j].size();

        rasterised_points_t x_left = edge_2[edge_2_size - 1 - j][edge_2_i_size - 1], x_right = edge_3[i][0];

        if (x_left.point.get_x() > x_right.point.get_x()){
            swap_rasterised_points(x_left, x_right);
        }
        double x_left_value = x_left.point.get_x(), x_right_value = x_right.point.get_x();
        double I_left = x_left.intensity, I_right = x_right.intensity;

        for (int x = x_left_value, y = edge_3[i][0].point.get_y();
              x <= x_right_value && x < SCREEN_WIDTH && y < SCREEN_HEIGHT; x++)
        {

            if (fabs(x_left_value - x) == 0){
                intensity = I_left;
            }
            else{
                t = (fabs(x_left_value - x)) / (fabs(x_left_value - x_right_value));
                intensity = (1 - t) * I_left + t * I_right;
            }

            point.point = Point2D<double>(x, y);
            point.intensity = intensity;
            temp_points.push_back(point);
        }
        rasterized_points.push_back(temp_points);
        temp_points.clear();
    }
}

/*!
 * \brief find_rasterize_points_right_top
 * \param rasterized_points
 * \param edge_1 -- array of pixel coordinates
 * \param edge_2 -- array of pixel coordinates
 * find rasterized (2d coordinate) pixels of top part (in screen) triangle
 * which middle point (x coordinate) locates right than max
 */
void find_rasterize_points_right_top(
                   std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                   std::vector<std::vector<rasterised_points_t>> &edge_1,
                   std::vector<std::vector<rasterised_points_t>> &edge_2)
{
    double t = 0, intensity = 0;
    std::vector<rasterised_points_t> temp_points;
    rasterised_points_t point;
    int edge_1_i_size;
    int edge_1_size = edge_1.size();

    for (int i = 0; i < edge_1_size; i++)
    {
        edge_1_i_size = edge_1[i].size();

        rasterised_points_t x_left = edge_2[i][0], x_right = edge_1[i][edge_1_i_size - 1];

        if (x_left.point.get_x() > x_right.point.get_x()){
            swap_rasterised_points(x_left, x_right);
        }
        double x_left_value = x_left.point.get_x(), x_right_value = x_right.point.get_x();
        double I_left = x_left.intensity, I_right = x_right.intensity;

        for (int x = x_left_value, y = edge_2[i][0].point.get_y();
               x <= x_right_value && x < SCREEN_WIDTH && y < SCREEN_HEIGHT; x++)
        {
            if (fabs(x_left_value - x) == 0){
                intensity = I_left;
            }
            else{
                t = (fabs(x_left_value - x)) / (fabs(x_left_value - x_right_value));
                intensity = (1 - t) * I_left + t * I_right;
            }

            point.point = Point2D<double>(x, y);
            point.intensity = intensity;
            temp_points.push_back(point);
        }
        rasterized_points.push_back(temp_points);
        temp_points.clear();
    }
}

/*!
 * \brief find_rasterize_points_left_bottom
 * \param rasterized_points
 * \param edge_2 -- array of pixel coordinates
 * \param edge_3 -- array of pixel coordinates
 *
 * find rasterized (2d coordinate) pixels of bottom part (in screen) triangle
 * which middle point (x coordinate) locates left than max
 */
void find_rasterize_points_left_bottom(
              std::vector<std::vector<rasterised_points_t>> &rasterized_points,
              std::vector<std::vector<rasterised_points_t>> &edge_2,
              std::vector<std::vector<rasterised_points_t>> &edge_3)
{
    double t = 0, intensity = 0;
    std::vector<rasterised_points_t> temp_points;
    rasterised_points_t point;
    int edge_2_i_size;

    int edge_3_size = edge_3.size(),
         edge_2_size = edge_2.size();

    for (int i = edge_3_size - 1, j = 0; i >=0; i--, j++)
    {
        edge_2_i_size = edge_2[edge_2_size - 1 - j].size();
        rasterised_points_t x_left = edge_3[i][0], x_right = edge_2[edge_2_size - 1 - j][edge_2_i_size - 1];

        if (x_left.point.get_x() > x_right.point.get_x()){
            swap_rasterised_points(x_left, x_right);
        }

        double x_left_value = x_left.point.get_x(), x_right_value = x_right.point.get_x();
        double I_left = x_left.intensity, I_right = x_right.intensity;

        for (int y = edge_3[i][0].point.get_y(), x = x_left_value;
              x <= x_right_value && x < SCREEN_WIDTH && y < SCREEN_HEIGHT; x++)
        {
            if (fabs(x_left_value - x) == 0){
                intensity = I_left;
            }
            else{
                t = (fabs(x_left_value - x)) / (fabs(x_left_value - x_right_value));
                intensity = (1 - t) * I_left + t * I_right;
            }

            point.point = Point2D<double>(x, y);
            point.intensity = intensity;
            temp_points.push_back(point);
        }
        rasterized_points.push_back(temp_points);
        temp_points.clear();
    }
}

/*!
 * \brief find_rasterize_points_left_top
 * \param rasterized_points
 * \param edge_1 -- array of pixel coordinates
 * \param edge_2 -- array of pixel coordinates
 *
 * find rasterized (2d coordinate) pixels of top part  (in scren) triangle
 * which middle point (x coordinate) locates left than max
 */
void find_rasterize_points_left_top(
                   std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                   std::vector<std::vector<rasterised_points_t>> &edge_1,
                   std::vector<std::vector<rasterised_points_t>> &edge_2)
{
    //для интерполяции
    double t = 0, intensity = 0;

    //растеризованные точки в ряду
    std::vector<rasterised_points_t> temp_points;

    //если серединная вершина треугольника лежит левее максимальной
    rasterised_points_t point;

    int edge_1_size = edge_1.size();
    int edge_1_i_size, edge_2_i_size;
    for (int i = 0; i < edge_1_size; i++)
    {
        edge_1_i_size = edge_1[i].size();
        edge_2_i_size = edge_2[i].size();

        rasterised_points_t x_left = edge_1[i][edge_1_i_size - 1], x_right = edge_2[i][edge_2_i_size - 1];

        if (x_left.point.get_x() > x_right.point.get_x()){
            swap_rasterised_points(x_left, x_right);
        }

        double x_left_value = x_left.point.get_x(), x_right_value = x_right.point.get_x();
        double I_left = x_left.intensity, I_right = x_right.intensity;

        for (int y = edge_1[i][0].point.get_y(), x = x_left_value;
              x <= x_right_value && x < SCREEN_WIDTH && y < SCREEN_HEIGHT; x++)
        {
            if (fabs(x_left_value - x) == 0){
                intensity = I_left;
            }
            else{
                t = (fabs(x_left_value - x)) / (fabs(x_left_value - x_right_value));
                intensity = (1 - t) * I_left + t * I_right;
            }

            point.point = Point2D<double>(x, y);
            point.intensity = intensity;
            temp_points.push_back(point);
        }
        rasterized_points.push_back(temp_points);
        temp_points.clear();
    }
}

Point3D<int> rasterize_triangle(std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                                    Triangle3D<double>&triangle, Triangle3D<double>&triangle_normals,
                                    Point3D<int> &light_position,
                                    std::vector<std::vector<QColor>> &colors, plane_coeffs_t &plane_coeffs)
{
    std::vector<std::vector<rasterised_points_t>> rasterized_points_up, rasterized_points_down;
    std::vector<std::vector<rasterised_points_t>> edge_1, edge_2, edge_3;
    Point3D<int> min_point, max_point, middle_point;
    std::array<Point3D<int>, 3> points;

    //triangle_normals.output();

    //find plane equation coeffs for triangle
    plane_coeffs = find_equation_plane(triangle[0], triangle[1], triangle[2]);

    //find min, middle, max points of triangle, located in screen
    /*std::cout << "triangle[0] = "; triangle[0].output_point();
    std::cout << "triangle[1] = "; triangle[1].output_point();
    std::cout << "triangle[2] = "; triangle[2].output_point();*/
    points = define_points_sort_inc(triangle[0], triangle[1], triangle[2], triangle_normals);
    min_point = points[0], middle_point = points[1], max_point = points[2];
    /*std::cout << "min_point = "; min_point.output_point();
    std::cout << "middle_point = "; middle_point.output_point();
    std::cout << "max_point = "; max_point.output_point();*/

    //find pixel coordinates for triangle edges
    edge_1 = create_line_by_int_brezenhem(min_point, middle_point, triangle_normals[0],
                                                                     triangle_normals[1], light_position, plane_coeffs);
    //std::cout << "edge_1 size: " << edge_1.size() << std::endl;
    edge_2 = create_line_by_int_brezenhem(min_point, max_point, triangle_normals[0],
                                                                     triangle_normals[2], light_position, plane_coeffs);
    edge_3 = create_line_by_int_brezenhem(middle_point, max_point,
                                                                     triangle_normals[1], triangle_normals[2], light_position, plane_coeffs);

    if (middle_point.get_x() <= max_point.get_x())
    {
        find_rasterize_points_left_top(rasterized_points, edge_1, edge_2);
        find_rasterize_points_left_bottom(rasterized_points, edge_2, edge_3);
    }
    else
    {
        find_rasterize_points_right_top(rasterized_points, edge_1, edge_2);
        find_rasterize_points_right_bottom(rasterized_points, edge_2, edge_3);
    }

    return middle_point;
}

double find_depth_pixel(int rasterize_x, int rasterize_y, plane_coeffs_t &plane_coeffs, double zbuffer_value)
{
    double z = zbuffer_value;
    if (plane_coeffs.c != 0){
        z = -(plane_coeffs.a * rasterize_x + plane_coeffs.b * rasterize_y + plane_coeffs.d) / plane_coeffs.c;
    }
    else{
        //qDebug() << "Деление на ноль.\n";
    }
    return z;
}

void find_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix,
                                            std::vector<std::vector<QColor>> &color_matrix,
                                            std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                                            plane_coeffs_t &plane_coeffs, Point3D<int> &light_position,
                                            Triangle3D<double>&triangle_normals, Triangle3D<double>points_3d)
{
    //направление света
    Vector3D<double> light_direction;

    //глубина пикселя
    double z = 0;

    rasterised_points_t rasterize_point;
    int rasterize_x_value = 0, rasterize_y_value = 0;

    //исходный цвет
    int r = 119, g =221, b = 119;
    //выходной цвет
    int r_in = 0, g_in = 0, b_in = 0;

    int size_row = rasterized_points.size(), size_column = 0;

    for (int i = 0; i < size_row; i++)
    {
        size_column = rasterized_points[i].size();
        for (int j = 0; j < size_column; j++)
        {
            rasterize_point = rasterized_points[i][j];
            rasterize_x_value = rasterize_point.point.get_x();
            rasterize_y_value = rasterize_point.point.get_y();

            z = find_depth_pixel(rasterize_x_value, rasterize_y_value, plane_coeffs,
                                             zbuffer_matrix[rasterize_x_value][rasterize_y_value]);

            if (z > zbuffer_matrix[rasterize_x_value][rasterize_y_value])
            {
                zbuffer_matrix[rasterize_x_value][rasterize_y_value] = z;

                r_in = r * rasterize_point.intensity;
                g_in = g * rasterize_point.intensity;
                b_in = b * rasterize_point.intensity;

                color_matrix[rasterize_x_value][rasterize_y_value].setRgb(r_in, g_in, b_in);
            }
        }
    }
}

bool is_equal_colors(QColor color_1, QColor color_2)
{
    bool is_equal = false;

    if (color_1.red() == color_2.red() && color_1.green() == color_2.green() &&
        color_1.blue() == color_2.blue())
    {
        is_equal = true;
    }

    return is_equal;
}

void ZBuffer::_init_zbuffer(int width, int height)
{
    _width = width, _height = height;
    std::cerr << "width_z_buffer: " << width << " height_zBuffer: " << height << "\n";

    std::vector<double> temp;
    std::vector<QColor> temp_color;

    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            temp.push_back(std::numeric_limits<int>::min());
            temp_color.push_back(QColor(255, 255, 255)); // в идеале поменять бы на текущий цвет фона
        }

        _zbuffer_matrix.push_back(temp);
        _color_matrix.push_back(temp_color);
        temp.clear();
        temp_color.clear();
    }
}

ZBuffer::~ZBuffer()
{
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _zbuffer_matrix[i].clear();
            _color_matrix[i].clear();
        }
    }

     _zbuffer_matrix.clear();
     _color_matrix.clear();
}

double ZBuffer::get_z_point(int index_i, int index_j) const{
    return _zbuffer_matrix[index_i][index_j];
}

void ZBuffer::set_z_point(int index_i, int index_j, double value){
    _zbuffer_matrix[index_i][index_j] = value;
}

std::vector<std::vector<double>> &ZBuffer::get_zbuffer_matrix(){
    return _zbuffer_matrix;
}

std::vector<std::vector<QColor>> &ZBuffer::get_color_matrix(){
    return _color_matrix;
}

int ZBuffer::get_width() const{
    return _width;
}

int ZBuffer::get_height() const{
    return _height;
}

/*!
 * \brief ZBuffer::is_background -- check if a pixel is background
 * \param index_i -- pixel color position in zbuffer
 * \param index_j -- pixel color position in zbuffer
 * \return true if success, else false
 */

bool ZBuffer::is_background(int index_i, int index_j)
{
    bool is_background = false;
    int r = 0, g = 0, b = 0;
    _color_matrix[index_i][index_j].getRgb(&r, &g, &b);
    if (r == 255 && g == 255 && b == 255)
        is_background = true;

    return is_background;
}

/*!
 * \brief ZBuffer::is_equal_colors -- check if colors are equal
 * \param index_i -- pixel color position in zbuffer
 * \param index_j -- pixel color position in zbuffer
 * \param rgb -- color
 * \return true if success, else false
 */

void ZBuffer::set_color(int index_i, int index_j, QRgb color){
    _color_matrix[index_i][index_j].setRgb(color);
}

/*!
 * \brief ZBuffer::reset -- reset zbuffer to default
 */
void ZBuffer::reset()
{
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _zbuffer_matrix[i][j] = std::numeric_limits<int>::min();
            _color_matrix[i][j] = QColor(255, 255, 255);
        }
    }
}

void ZBuffer::set_buffer_matrix(std::vector<std::vector<double>> buffer_matrix){
    _zbuffer_matrix = buffer_matrix;
}

void ZBuffer::set_color_matrix(std::vector<std::vector<QColor>> color_matrix){
    _color_matrix = color_matrix;
}

void ZBuffer::convert_color_to_black_and_white()
{
    int r, g, b, grey;
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _color_matrix[i][j].getRgb(&r, &g, &b);
            grey = 0.36 * r + 0.53 * g + 0.11 * b;
            _color_matrix[i][j].setRgb(qRgb(grey, grey, grey));
        }
    }
}

