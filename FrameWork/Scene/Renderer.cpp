#include "Renderer.h"
#include "Material.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
GameEngineBegin 

extern SceneManager *g_pSceneManager;

void Renderer::Prepare()
{
    // for (int i = 0; i < m_Materials.size(); ++i)
    // {
    //     auto &material = m_Materials[i];
    //     if (material)
    //     {
    //         material->Prepare();
    //     }
    // }
}

Renderer::Renderer() : Component(ClassIDType::CLASS_Undefined)
{
}

SharedMesh Renderer::getMesh()
{
    return SharedMesh();
}

std::vector<SharedMaterial> Renderer::getMaterials()
{
    return m_Materials;
}

void Renderer::AddMaterial(SharedMaterial material)
{
    m_Materials.push_back(material);
}

void Renderer::Render(SharePtr<Camera> camera)
{
}

void Renderer::Start()
{
    if (m_Started)
        return;
    auto renderer = getParent()->getComponent<Renderer>();
    if (!renderer)
        return;
    auto scene = g_pSceneManager->GetScene();
    scene->AddRenderer(std::dynamic_pointer_cast<Renderer>(renderer));
    Component::Start();
}

GameEngineEnd
