#include "ShadowPass.h"

#include "../GraphicsManager.h"
#include "Frustum.h"
#include "GameObject.h"
#include "GraphicsFunc.h"
#include "IntersectionTests.h"
#include "Light.h"
#include "MeshRenderer.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderBase.h"
#include "ShaderManager.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern GraphicsManager *g_pGraphicsManager;
    extern SceneManager *g_pSceneManager;
    void ShadowPass::Initialize()
    {
        m_ShaderID = g_pShaderManager->AddShaderByPath("Shaders/sample_shadow.vert", "Shaders/sample_shadow.frag");
        m_ShaderID2 = g_pShaderManager->AddShaderByPath("Shaders/write_depth.vert", "Shaders/write_depth.frag");
    }

    void ShadowPass::BeginDraw()
    {
    }

    void ShadowPass::Draw(SharedCamera camera)
    {
        float splitPostions[5];
        camera->CalculateSplitPositions(splitPostions, 4);
        auto shader = g_pShaderManager->GetShaderProgram(m_ShaderID2);
        shader->Use();

        Frame &frame = g_pGraphicsManager->GetFrame();
        auto scene = g_pSceneManager->GetScene();
        auto lights = scene->GetLights();

        uint32_t index = 0;
        for (auto light : lights)
        {
            shader->setInt("layer_index", index);
            auto lightTrans = light->GetParent()->GetComponent<Transform>();
            glm::mat4 viewM = lightTrans->GetViewMatrix();
            for (size_t num = 0; num < 4; num++)
            {
                Frustum frustum = camera->CalculateFrustum(splitPostions[num], splitPostions[num + 1]);
                std::vector<SharedGameObject> calculates;
                for (auto child : scene->GetChildren())
                {
                    if (IntersectionTest(child.second->GetAABB(), frustum))
                        calculates.push_back(child.second);
                }

                glm::mat4 mCropMatrix = light->CalculateCropMatrix(frustum);
                shader->setMat4("projectionMatrix", mCropMatrix);
                GraphicsFunc::GetShadowArray(frame.shadowInfos.shadows[num]);
                GraphicsFunc::BeginShadow(index, frame.shadowInfos.shadows[num], frame.shadowInfos.shadowFBO);

                std::vector<SharedGameObject> games;

                for (auto child : scene->GetChildren())
                {
                    if (IntersectionTest(child.second->GetAABB(), frustum))
                        games.push_back(child.second);
                    auto meshRender = child.second->GetComponent<MeshRenderer>();
                    auto modelMat = child.second->GetComponent<Transform>()->GetMatrix();
                    ModelInfos infos;
                    memcpy(infos.modelMat4, glm::value_ptr(modelMat), sizeof(float) * 16);
                    GraphicsFunc::SetModelInfos(infos, frame);
                    GraphicsFunc::SetUBOData(shader, frame);

                    if (meshRender && meshRender->GetMesh())
                    {
                        auto mesh = meshRender->GetMesh();
                        for (size_t mi = 0; mi < mesh->m_MeshDatas.size(); mi++)
                        {
                            ModelRenderConfig config;
                            config.index = mi;
                            config.mesh = mesh;
                            GraphicsFunc::PrepareMesh(config);
                        }
                    }
                }
                GraphicsFunc::EndShadow(frame.shadowInfos.shadowFBO);
            }

            index++;
        }
    }

    void ShadowPass::EndDraw()
    {
    }

}  // namespace GameEngine