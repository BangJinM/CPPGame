#pragma once

#include <list>
#include <map>
#include <memory>

#include "Config.h"
#include "IRuntimeModule.h"
#include "Material.h"
#include "Mesh.h"
#include "MyMath.h"
#include "Render/IDrawPass.h"
#include "Renderer.h"

namespace GameEngine
{
    class Scene;

    class BaseGraphicsManager : public IRuntimeModule
    {
    public:
        virtual ~BaseGraphicsManager() {}

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick(float deltaTime);
        virtual void Clear();
        virtual void Draw();

        void AddRendererCommand(SharedMaterial, ModelRenderConfig);
        std::map<int, RendererCammand> GetRendererCommand();

        virtual void PrepareMesh(ModelRenderConfig) = 0;
        virtual void BindTexture(SharedTexture texture) = 0;
        virtual void BindCubeTexture(SharedCube cube) = 0;
        virtual void DrawCubeTexture(SharedCube cube, int shaderID) = 0;
        virtual void PrepareMaterial(SharedMaterial) = 0;

        virtual void SetUBOData(SharedShaderProgramBase shader) = 0;

        virtual void SetTexture(SharedShaderProgramBase shader, std::string name, int id) = 0;
        virtual void SetLightInfo(const LightInfo& lightInfo) = 0;
        virtual void SetViewInfos(const ViewInfos& infos) = 0;
        virtual void SetModelInfos(const ModelInfos& infos) = 0;

        virtual void CalculateLights();

        virtual void BeginShadow(LightInfo info, int layerIndex) = 0;
        virtual void EndShadow() = 0;
        virtual int GetShadowArray(int count) = 0;
        virtual void DeleteShadowArrsy() = 0;

        virtual int GetFrameBufferObject() = 0;
        virtual void DeleteFrameBufferObject() = 0;

        LightInfo GetLightInfo();

    protected:
        std::map<int, RendererCammand> m_RendererCommands;
        std::list<std::shared_ptr<IDrawPass>> m_IDrawPass;

        LightInfo m_LightInfos;
    };

    extern BaseGraphicsManager* g_pGraphicsManager;
}  // namespace GameEngine
