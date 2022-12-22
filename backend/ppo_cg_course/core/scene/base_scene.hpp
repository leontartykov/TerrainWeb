#ifndef _BASE_SCENE_HPP_
#define _BASE_SCENE_HPP_

#include <QColor>
#include <QGraphicsScene>
#include <QPainter>

#include "core/scene/scene_struct.h"

typedef struct scene_window scene_win_t;
struct scene_window
{
    int min_x, max_x;
    int min_y, max_y;
};

class IScene
{
    public:
        virtual ~IScene() {};
        virtual std::pair<std::vector<std::vector<QColor>>, scene_win_t>
            create_scene(all_scene_info_t &scene_info) = 0;
        virtual void build_scene(all_scene_info_t &scene_info) = 0;
        virtual void draw_scene(QGraphicsScene *scene, QGraphicsView *view) = 0;
};

#endif
