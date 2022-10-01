#include <iostream>
#include "../../../scene/scene_commands/scene_command_base.h"

class SceneCommand: public BaseSceneCommand {};

class RenderSceneCmd: public SceneCommand
{
    public:
        RenderSceneCmd() = default;
        ~RenderSceneCmd() = default;

        virtual void execute() override;
};

class TransformCmd: public BaseSceneCommand {};

class TransformObject3D: public TransformCmd
{
    public:
        TransformObject3D() = default;
        ~TransformObject3D() = default;

        virtual void execute() override;
};

class TerrainCmd: public BaseSceneCommand {};

class BaseLoadTerrain: public TerrainCmd {};
class BaseExportTerrain: public TerrainCmd {};

class LoadFileTxt: public BaseLoadTerrain
{
    public:
        LoadFileTxt() = default;
        ~LoadFileTxt() = default;

        virtual void execute() override;
};

class LoadFileBmp: public BaseLoadTerrain
{
    public:
        LoadFileBmp() = default;
        ~LoadFileBmp() = default;

        virtual void execute() override;
};

class ExportFileTxt: public BaseExportTerrain
{
    public:
        ExportFileTxt() = default;
        ~ExportFileTxt() = default;

        virtual void execute() override;
};

class ExportFileBmp: public BaseExportTerrain
{
    public:
        ExportFileBmp() = default;
        ~ExportFileBmp() = default;

        virtual void execute() override;
};
