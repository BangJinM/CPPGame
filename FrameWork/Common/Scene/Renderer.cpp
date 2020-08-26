#include "Renderer.h"
#include "Material.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
namespace GameEngine
{
    void Renderer::Prepare()
    {
        for (int i = 0; i < m_Materials.size(); ++i)
        {
            auto &material = m_Materials[i];
            if (material)
            {
                material->Prepare();
            }
        }
    }

    Renderer::Renderer() : Component(ClassIDType::CLASS_Undefined)
    {
    }

    std::shared_ptr<Mesh> Renderer::getMesh()
    {
        return std::shared_ptr<Mesh>();
    }

    std::vector<std::shared_ptr<Material>> Renderer::getMaterials()
    {
        return m_Materials;
    }

    void Renderer::AddMaterial(std::shared_ptr<Material> material)
    {
        m_Materials.push_back(material);
    }

    void Renderer::Render(std::shared_ptr<Camera> camera)
    {
    }

    void Renderer::Start()
    {
        if (m_Started)
            return;
        auto renderer = getParent()->getComponent<Renderer>();
        if (!renderer)
            return;
        auto scene = SceneManager::GetInstance()->GetScene();
        scene->AddRenderer(std::dynamic_pointer_cast<Renderer>(renderer));
        Component::Start();
    }

} // namespace GameEngine
