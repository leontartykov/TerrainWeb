#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include "core/scene/base_scene.hpp"
#include "core/object/terrain/terrain.h"

class Scene: public IScene
{
    public:
        Scene();
        virtual ~Scene() override;

        void set_terrain(Terrain *terrain);
        void set_zbuffer(ZBuffer *zbuffer);

        virtual void build_scene(all_scene_info_t &scene_info) override;
        virtual void draw_scene(QGraphicsScene *scene, QGraphicsView *view) override;
        virtual std::pair<std::vector<std::vector<QColor>>, scene_win_t>
            create_scene(all_scene_info_t &scene_info) override;

        Terrain *get_terrain();
        ZBuffer *get_zbuffer();

        //int export_terrain();
        //int load_terrain();

        void convert_color_to_black_and_white();


        bool is_background_color(QColor &color);

    private:
        Terrain *_terrain;
        ZBuffer *_zbuffer;
};

#endif
