#ifndef _SCENE_COMMAND_BASE_H_
#define _SCENE_COMMAND_BASE_H_

#include <iostream>
#include <memory>

class BaseSceneCommand{
    public:
        virtual ~BaseSceneCommand() = 0;
        virtual void execute() = 0;
};

#endif
