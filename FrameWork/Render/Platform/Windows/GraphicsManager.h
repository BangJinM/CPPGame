#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Config.h"
#include "Render/BaseGraphicsManager.h"

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
        virtual void PrepareMesh(ModelRenderConfig) override;
        virtual void PrepareMaterial(SharedMaterial) override;

        virtual void SetUBOData(SharedShaderProgramBase shader) override;

        virtual void SetLightInfo(const LightInfo& lightInfo) override;
        virtual void SetViewInfos(const ViewInfos& infos) override;
        virtual void SetModelInfos(const ModelInfos& infos) override;

        virtual void BeginShadow(LightInfo info, int layerIndex) override;
        virtual void EndShadow() override;
        virtual int GetShadowArray(int count) override;
        virtual void DeleteShadowArrsy() override;

        virtual int GetFrameBufferObject() override;
        virtual void DeleteFrameBufferObject() override;

        int m_uboLightInfo = -1;
        int m_uboCameraInfo = -1;
        int m_uboModelInfo = -1;
        int m_uboLightModelInfo = -1;

        unsigned int shadowMap = 0;
        unsigned int shadowFBO = 0;
    };

}  // namespace GameEngine