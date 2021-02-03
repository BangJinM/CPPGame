#pragma once

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

        virtual void Tick();
        virtual void Clear();

        virtual void BindTexture(SharedTexture texture) override;
        virtual void PrepareMesh(SharedMesh mesh, int index) override;
        virtual void PrepareMaterial(SharedMaterial material) override;
    };

}  // namespace GameEngine