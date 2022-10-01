#ifndef _TERRAIN_FACADE_H_
#define _TERRAIN_FACADE_H_

#include "../../../scene/scene_commands/scene_command_base.h"

class TerrainFacade
{
    public:
        TerrainFacade() = default;
        ~TerrainFacade() = default;
        void execute(std::shared_ptr<BaseSceneCommand> cmd);
};

#endif
