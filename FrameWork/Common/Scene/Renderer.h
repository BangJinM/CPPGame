#ifndef GameEngine_Common_Scene_Renderer_H
#define GameEngine_Common_Scene_Renderer_H

#include "MyMath.h"
#include <list>
#include "Component.h"
#include "Material.h"
#include "Mesh.h"
namespace GameEngine
{
    class Renderer : public Component
    {
    public:


        void Prepare();
        Renderer();
        std::shared_ptr<Mesh> getMesh(){return std::shared_ptr<Mesh>();}
        std::vector<std::shared_ptr<Material>> getMaterials(){return m_Materials;}

    protected:

        std::vector<std::shared_ptr<Material>> m_Materials;
    };
} // namespace GameEngine
#endif