#include "terrain_facade.h"

void TerrainFacade::execute(std::shared_ptr<BaseSceneCommand> cmd){
    cmd->execute();
}
