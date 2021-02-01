#include "MeshRenderer.h"

#include "BaseGraphicsManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Material.h"
#include "Transform.h"
#include "glm/glm.hpp"
namespace GameEngine
{
    extern BaseGraphicsManager *g_pGraphicsManager;
    MeshRenderer::MeshRenderer()
    {
    }

    void MeshRenderer::Render(SharePtr<Camera> camera)
    {
        auto viewMat = camera->getParent()->getComponent<Transform>()->getMatrix();
        auto projectMat = camera->getProjectionMatrix();

        SharedGameObject parent = getParent();
        auto modelMat = parent->getComponent<Transform>()->getMatrix();
        SharedMesh mesh = getMesh();
        auto materials = getMaterials();
        for (size_t mi = 0; mi < mesh->m_MeshDatas.size(); mi++)
        {
            int materialID = 0;
            if (materials[materialID])
            {
                if (mi < materials.size())
                    materialID = mi;
                Material material = (*materials[materialID]);
                material.AddProperty(glm::value_ptr(projectMat), "projection", 16 * sizeof(float), MaterialType::T_Mat4);
                material.AddProperty(glm::value_ptr(viewMat), "view", 16 * sizeof(float), MaterialType::T_Mat4);
                material.AddProperty(glm::value_ptr(modelMat), "model", 16 * sizeof(float), MaterialType::T_Mat4);

                if (mesh && mi <= mesh->m_MeshDatas.size())
                {
                    RendererCammand rC;
                    rC.material = material;
                    rC.mesh = mesh;
                    rC.index = mi;

                    g_pGraphicsManager->addRendererCommand(rC);
                }
            }
        }
    }
}  // namespace GameEngine