#include "MeshRenderer.h"

#include "AssetManager.h"
#include "BaseGraphicsManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Material.h"
#include "Transform.h"
#include "glm/glm.hpp"

namespace GameEngine
{
    extern BaseGraphicsManager* g_pGraphicsManager;
    extern AssetManager* g_pAssetManager;

    MeshRenderer::MeshRenderer()
    {
        m_ClassID = ClassID(MeshRenderer);
    }

    void MeshRenderer::Render(ViewInfos viewInfos)
    {
        SharedGameObject parent = GetParent();
        auto modelMat = parent->getComponent<Transform>()->GetMatrix();
        SharedMesh mesh = getMesh();
        auto materials = getMaterials();
        for (size_t mi = 0; mi < mesh->m_MeshDatas.size(); mi++)
        {
            int materialID = 0;
            if (materials[materialID])
            {
                if (mi < materials.size())
                    materialID = mi;
                SharedMaterial material = make_shared<Material>();
                material->shaderID = materials[mi]->shaderID;
                material->AddPropertys(materials[mi]->m_MaterialDatas);

                if (mesh && mi <= mesh->m_MeshDatas.size())
                {
                    RendererCammand rC;
                    rC.material = material;
                    rC.mesh = mesh;
                    rC.viewInfos = viewInfos;

                    rC.modelInfos.modelMat4 = modelMat;
                    rC.index = mi;

                    g_pGraphicsManager->addRendererCommand(rC);
                }
            }
        }
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