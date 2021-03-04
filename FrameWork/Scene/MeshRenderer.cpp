#include "MeshRenderer.h"

#include "AssetManager.h"
#include "GameObject.h"
#include "Material.h"
#include "Transform.h"
#include "glm/glm.hpp"

namespace GameEngine
{
    extern AssetManager* g_pAssetManager;

    MeshRenderer::MeshRenderer()
    {
        m_ClassID = ClassID(MeshRenderer);
    }

    void MeshRenderer::OnSerialize(cJSON* root)
    {
        SerializableHelper::Seserialize(root, "m_Mesh", m_MeshPath);
        Renderer::OnSerialize(root);
    }
    void MeshRenderer::OnDeserialize(cJSON* root)
    {
        m_MeshPath = SerializableHelper::DeserializeString(root, "m_Mesh");
        SetMesh(g_pAssetManager->LoadMesh(m_MeshPath));
        Renderer::OnDeserialize(root);
    }
}  // namespace GameEngine