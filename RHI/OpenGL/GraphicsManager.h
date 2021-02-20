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
        virtual void SetLightInfo(const LightInfo& lightInfo) override;

		GLuint m_uboLightInfo;
    };

}  // namespace GameEngine