#include "app_facade.h"

void AppFacade::execute(std::shared_ptr<BaseAppCommand> cmd){
    cmd->execute();
}
