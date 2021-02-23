#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "BaseGraphicsManager.h"
#include "Config.h"

namespace GameEngine
{
    class MeshData;
    class Material;

    class GraphicsManager : public BaseGraphicsManager
    {
    public:
        virtual ~GraphicsManager() {}

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick(float deltaTime);
        virtual void Clear();

        virtual void BindTexture(SharedTexture texture) override;
        virtual void BindCubeTexture(SharedCube cube) override;
        virtual void DrawCubeTexture(SharedCube cube, int shaderID) override;
        virtual void PrepareMesh(SharedMesh mesh, int index) override;
        virtual void PrepareMaterial(RendererCammand rC) override;

        virtual void SetUBOData(SharedShaderProgramBase shader) override;

        virtual void SetLightInfo(const LightInfo& lightInfo) override;
        virtual void SetViewInfos(const ViewInfos& infos) override;
        virtual void SetModelInfos(const ModelInfos& infos) override;

        int m_uboLightInfo = -1;
        int m_uboCameraInfo = -1;
        int m_uboModelInfo = -1;
    };

}  // namespace GameEngine