# include "scene_command_base.h"

class SceneCommand: public BaseSceneCommand {};

class RenderScene: public SceneCommand
{
    public:
        RenderScene() = default;
        ~RenderScene() = default;

        virtual void execute() override;
};

class TerrainCommand: public BaseSceneCommand
{
    public:
        TerrainCommand() = default;
        ~TerrainCommand() = default;

        virtual void execute() override;
};

//class LightCommand: public SceneCommand

class TransformCommand: public BaseSceneCommand
{
    public:
        TransformCommand() = default;
        ~TransformCommand() = default;

        virtual void execute() override;
};
