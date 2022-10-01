#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QPixmap>
#include <memory>
#include <QApplication>

#include "../object/terrain/terrain.h"
#include "../object/light/light.h"
//#include "../invisible/zbuffer/zbuffer.hpp"
#include "../scene/scene_facade/scene_facade.h"
#include "../scene/scene.h"
#include "../scene/scene_struct.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow: public QMainWindow
{
        Q_OBJECT

    private:
        Ui::MainWindow *ui;
        QGraphicsScene *scene;
        QGraphicsView *view;
        QImage *image;
        QPixmap pixmap;

        std::shared_ptr<SceneFacade> _scene_facade;
        Scene _scene;

     public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

     public slots:
        void rotate_terrain();
        void change_noise_parametrs();

        void scale_landscape();
        void change_color_to_black_white();
};

#endif
