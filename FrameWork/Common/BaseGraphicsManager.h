#pragma once

#include <list>
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

        void addRendererCommand(RendererCammand command);
        std::list<RendererCammand> getRendererCommand();

        virtual void PrepareMesh(SharedMesh mesh, int index) = 0;
        virtual void BindTexture(SharedTexture texture) = 0;
        virtual void BindCubeTexture(SharedCube cube) = 0;
        virtual void DrawCubeTexture(SharedCube cube, int shaderID) = 0;
        virtual void PrepareMaterial(RendererCammand rC) = 0;
        virtual void SetLightInfo(const LightInfo& lightInfo) = 0;

		virtual void CalculateLights();

    protected:
        std::list<RendererCammand> m_RendererCommands;
        std::list<std::shared_ptr<IDrawPass>> m_IDrawPass;

        LightInfo m_LightInfos;
    };

    extern BaseGraphicsManager *g_pGraphicsManager;
}  // namespace GameEngine
