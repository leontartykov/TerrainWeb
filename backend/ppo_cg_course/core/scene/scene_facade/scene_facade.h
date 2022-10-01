#ifndef _SCENE_FACADE_H_
#define _SCENE_FACADE_H_

#include <memory>
#include "../scene_commands/scene_command_base.h"

class SceneFacade
{
    public:
        SceneFacade() = default;
        ~SceneFacade() = default;
        void execute(std::shared_ptr<BaseSceneCommand> cmd);
};

#endif
