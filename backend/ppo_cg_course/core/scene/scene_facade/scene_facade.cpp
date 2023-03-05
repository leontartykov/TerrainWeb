#include "scene_facade.h"

void SceneFacade::execute(std::shared_ptr<BaseSceneCommand> cmd){
    cmd->execute();
}
