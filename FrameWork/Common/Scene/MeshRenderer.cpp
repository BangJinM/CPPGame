#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "Material.h"
#include "GameObject.h"
namespace GameEngine
{
    MeshRenderer::MeshRenderer()
    {
    }

    void MeshRenderer::Render(std::shared_ptr<Camera> camera)
    {
		auto viewMat = camera->getParent()->getComponent<Transform>()->getMatrix();
		auto projectMat = camera->getProjectionMatrix();

        std::shared_ptr<GameObject> parent = getParent();
        auto modelMat = parent->getComponent<Transform>()->getMatrix();
        std::shared_ptr<Mesh> mesh = getMesh();
        auto materials = getMaterials();
        for (size_t mi = 0; mi < mesh->m_MeshDatas.size(); mi++)
        {
            int materialID = 0;
            if (materials[materialID])
            {
                if (mi < materials.size())
                    materialID = mi;
                auto material = Material::createMaterial(materials[materialID]);
                material->AddProperty(glm::value_ptr(projectMat), "projection", 16 * sizeof(float), MaterialType::T_Mat4);
                material->AddProperty(glm::value_ptr(viewMat), "view", 16 * sizeof(float), MaterialType::T_Mat4);
                material->AddProperty(glm::value_ptr(modelMat), "model", 16 * sizeof(float), MaterialType::T_Mat4);
                material->Prepare();
                if (mesh && mi <= mesh->m_MeshDatas.size())
                {
                    auto meshdata = mesh->m_MeshDatas[mi];
                    glBindVertexArray(meshdata.VAO);
                    glDrawElements(GL_TRIANGLES, meshdata.indices.size(), GL_UNSIGNED_INT, 0);
                    glBindVertexArray(0);
                }
            }
        }
    }
} // namespace GameEngine