#include "scene_builder.h"

std::shared_ptr<Terrain> SceneBuilder::get_terrain()
{
    if (!terrain){
        terrain = create_terrain();
    }

    return terrain;
}

std::shared_ptr<Terrain> ScenePerlinBuilder::create_terrain()
{
    terrain = std::make_shared<Terrain>();
    return terrain;
}

std::shared_ptr<Terrain> SceneDirector::create(std::shared_ptr<SceneBuilder> builder){
    if (builder->build_terrain()){
        return builder->get_terrain();
    }

    return std::shared_ptr<Terrain>();
}
