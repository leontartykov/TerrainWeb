#ifndef _SCENE_BUILDER_H_
#define _SCENE_BUILDER_H_

#include <memory>
//#include "../../object/terrain/terrain.hpp"
#include "../../object/terrain/terrain.h"

class SceneBuilder
{
    public:
        virtual bool build_terrain() = 0;
        //virtual void build_light() = 0;

        std::shared_ptr<Terrain> get_terrain();
    protected:
        virtual std::shared_ptr<Terrain> create_terrain() = 0;
        std::shared_ptr<Terrain> terrain;
};

class ScenePerlinBuilder: public SceneBuilder
{
    public:
        virtual bool build_terrain() override;
        //virtual void build_light() override;
    protected:
        virtual std::shared_ptr<Terrain> create_terrain() override;
};

class SceneDirector
{
    public:
        std::shared_ptr<Terrain> create(std::shared_ptr<SceneBuilder> builder);
};

#endif
