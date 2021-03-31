#pragma once

#include "../ISubPass.h"
#include "GameObject.h"
#include "GraphicsFunc.h"
#include "GraphicsManager.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "Transform.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern GraphicsManager *g_pGraphicsManager;
    extern SceneManager *g_pSceneManager;
    class ForwardPass : public ISubPass
    {
    public:
        virtual void Initialize() override
        {
        }

        virtual void BeginDraw() override
        {
        }

        virtual void Draw(SharedCamera camera) override
        {
            auto scene = g_pSceneManager->GetScene();
            auto m_Lights = scene->m_Lights;
            Frame &frame = g_pGraphicsManager->GetFrame();
            for (auto child : scene->GetChildren())
            {
                auto meshRender = child.second->GetComponent<MeshRenderer>();
                if (meshRender && meshRender->GetMesh())
                {
                    auto mesh = meshRender->GetMesh();
                    auto modelMat = child.second->GetComponent<Transform>()->GetMatrix();
                    auto materials = meshRender->GetMaterials();
                    int materialID = -1;
                    for (size_t mi = 0; mi < mesh->m_MeshDatas.size(); mi++)
                    {
                        if (mi < materials.size())
                            materialID = mi;
                        if (materialID >= 0)
                        {
                            ModelInfos infos;
                            GraphicsFunc::PrepareMaterial(materials[materialID], frame);
                            auto shader = g_pShaderManager->GetShaderProgram(materials[materialID]->shaderID);
                            memcpy(infos.modelMat4, glm::value_ptr(modelMat), sizeof(float) * 16);
                            GraphicsFunc::SetModelInfos(infos, frame);
                            GraphicsFunc::SetUBOData(shader, frame);
                        }
                        ModelRenderConfig config;
                        config.index = mi;
                        config.mesh = mesh;
                        GraphicsFunc::PrepareMesh(config);
                    }
                }
            }
        }

        virtual void EndDraw() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
