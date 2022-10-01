#ifndef _SCENE_H_
#define _SCENE_H_

#include <memory>
#include "../object/terrain/terrain.h"
#include "scene_struct.h"

class Scene
{
    public:
        Scene();
        ~Scene();

        void set_terrain(Terrain *terrain);
        void set_zbuffer(ZBuffer *zbuffer);
        void build_scene(all_scene_info_t &scene_info);
        void draw_scene(QGraphicsScene *scene, QGraphicsView *view);
        Terrain *get_terrain();
        ZBuffer *get_zbuffer();

        int export_terrain();
        int load_terrain();

        void convert_color_to_black_and_white();

    private:
        Terrain *_terrain;
        ZBuffer *_zbuffer;
};

#endif
