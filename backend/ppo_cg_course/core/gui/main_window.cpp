#include "main_window.h"
#include "ui_mainwindow.h"
#include "core/scene/scene_commands/scene_command_base.h"
#include "core/scene/scene_commands/scene_commands.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = ui->graphicsView;
    scene = new QGraphicsScene(ui->graphicsView);
    view->setScene(scene);
    view->show();

    QObject::connect(ui->spinbox_rotate_x, SIGNAL(valueChanged(int)), this, SLOT(rotate_terrain()));
    QObject::connect(ui->spinbox_rotate_y, SIGNAL(valueChanged(int)), this, SLOT(rotate_terrain()));
    QObject::connect(ui->spinbox_rotate_z, SIGNAL(valueChanged(int)), this, SLOT(rotate_terrain()));

    QObject::connect(ui->spinbox_octaves, SIGNAL(valueChanged(int)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_gain, SIGNAL(valueChanged(double)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_lacunarity, SIGNAL(valueChanged(double)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_seed, SIGNAL(valueChanged(int)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_frequency, SIGNAL(valueChanged(double)), this, SLOT(change_noise_parametrs()));

    QObject::connect(ui->spinbox_width_landscape, SIGNAL(valueChanged(int)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_height_landscape, SIGNAL(valueChanged(int)), this, SLOT(change_noise_parametrs()));

    QObject::connect(ui->spinbox_scale, SIGNAL(valueChanged(double)), this, SLOT(scale_landscape()));
    QObject::connect(ui->black_white_color, SIGNAL(released()), this, SLOT(change_color_to_black_white()));

    meta_data_t scene_meta_data = {.octaves = ui->spinbox_octaves->value(),
                                                .gain = ui->spinbox_gain->value(),
                                                .lacunarity = ui->spinbox_lacunarity->value(),
                                                .seed = ui->spinbox_seed->value(),
                                                .frequency = ui->spinbox_frequency->value()};

    rotate_t scene_rotate_angles = {.angle_x = ui->spinbox_rotate_x->value(),
                                            .angle_y = ui->spinbox_rotate_y->value(),
                                            .angle_z = ui->spinbox_rotate_z->value()};

    Point3D<int> scene_point_light_position(ui->spinbox_light_position_x->value(),
                                                           ui->spinbox_light_position_y->value(),
                                                           ui->spinbox_light_position_z->value());
    double scene_scale_coeff = ui->spinbox_scale->value();

    all_scene_info scene_info = {
        .scene_meta_data = scene_meta_data,
        .scene_rotate_terrain_angles = scene_rotate_angles,
        .scene_terrain_scale = scene_scale_coeff,
        .scene_point_light_position = scene_point_light_position
    };

    _scene.build_scene(scene_info);
    _scene.draw_scene(scene, view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rotate_terrain()
{
    Terrain* terrain = _scene.get_terrain();

    rotate_t rotate_angles, rotate_angles_landscape = terrain->get_rotate_angles();
    rotate_angles.angle_x = ui->spinbox_rotate_x->value() -  terrain->get_rotate_x();
    rotate_angles.angle_y = ui->spinbox_rotate_y->value() - terrain->get_rotate_y();
    rotate_angles.angle_z = ui->spinbox_rotate_z->value() - terrain->get_rotate_z();

    rotate_t new_angles = {
        .angle_x = terrain->get_rotate_x() + rotate_angles.angle_x,
        .angle_y = terrain->get_rotate_y() + rotate_angles.angle_y,
        .angle_z = terrain->get_rotate_z() + rotate_angles.angle_z
    };

    Point3D<int> scene_point_light_position(ui->spinbox_light_position_x->value(),
                                                           ui->spinbox_light_position_y->value(),
                                                           ui->spinbox_light_position_z->value());
    terrain->set_rotate_angles(new_angles);


    ZBuffer *zbuffer = _scene.get_zbuffer();
    zbuffer->reset();

    terrain->rotate_terrain(rotate_angles);
    terrain->transform_points_to_screen();
    terrain->remove_invisible_lines(*zbuffer, scene_point_light_position);

    _scene.set_terrain(terrain);
    _scene.set_zbuffer(zbuffer);

    _scene.draw_scene(scene, view);
}


void MainWindow::change_noise_parametrs()
{
    int width = ui->spinbox_width_landscape->value(), height = ui->spinbox_height_landscape->value();
    ZBuffer *zbuffer = _scene.get_zbuffer();
    Terrain* terrain = _scene.get_terrain();

    zbuffer->reset();
    terrain->clear();
    terrain->change_size(width, height);

    _scene.set_terrain(terrain);
    _scene.set_zbuffer(zbuffer);

    meta_data_t scene_meta_data = {.octaves = ui->spinbox_octaves->value(),
                                                .gain = ui->spinbox_gain->value(),
                                                .lacunarity = ui->spinbox_lacunarity->value(),
                                                .seed = ui->spinbox_seed->value(),
                                                .frequency = ui->spinbox_frequency->value()};

    rotate_t scene_rotate_angles = {.angle_x = ui->spinbox_rotate_x->value(),
                                            .angle_y = ui->spinbox_rotate_y->value(),
                                            .angle_z = ui->spinbox_rotate_z->value()};

    Point3D<int> scene_point_light_position(ui->spinbox_light_position_x->value(),
                                                           ui->spinbox_light_position_y->value(),
                                                           ui->spinbox_light_position_z->value());
    double scene_scale_coeff = ui->spinbox_scale->value();

    all_scene_info scene_info = {
        .scene_meta_data = scene_meta_data,
        .scene_rotate_terrain_angles = scene_rotate_angles,
        .scene_terrain_scale = scene_scale_coeff,
        .scene_point_light_position = scene_point_light_position
    };

    _scene.build_scene(scene_info);
    _scene.draw_scene(scene, view);
}


void MainWindow::scale_landscape()
{
    Terrain* terrain = _scene.get_terrain();

    ZBuffer *zbuffer = _scene.get_zbuffer();
    zbuffer->reset();

    double scene_scale_coeff = ui->spinbox_scale->value();
    terrain->scale_terrain(scene_scale_coeff);
    terrain->transform_points_to_screen();

    Point3D<int> scene_point_light_position(ui->spinbox_light_position_x->value(),
                                                           ui->spinbox_light_position_y->value(),
                                                           ui->spinbox_light_position_z->value());

    terrain->remove_invisible_lines(*zbuffer, scene_point_light_position);

    _scene.set_terrain(terrain);
    _scene.set_zbuffer(zbuffer);

    _scene.draw_scene(scene, view);
}

void MainWindow::change_color_to_black_white()
{
    _scene.convert_color_to_black_and_white();
    _scene.draw_scene(scene, view);
}
