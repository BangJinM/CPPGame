#include "CanvasRenderer.h"

#include "AssetManager.h"
#include "BaseGraphicsManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Widget.h"

namespace GameEngine
{
    extern SceneManager *g_pSceneManager;
    extern BaseGraphicsManager *g_pGraphicsManager;

    CanvasRenderer::CanvasRenderer(ClassIDType classID):MeshRenderer(classID)
    {
        m_Mesh = std::make_shared<Mesh>();
    }

    CanvasRenderer::~CanvasRenderer()
    {
    }

    void CanvasRenderer::addWidget(SharePtr<Widget> widget)
    {
        m_Widgets.push_back(widget);
    }

    void CanvasRenderer::getWidget()
    {
    }

    void CanvasRenderer::Update()
    {
    }

    void CanvasRenderer::Start()
    {
        if (m_Started)
            return;
        auto canvasRenderer = GetParent()->getComponent<CanvasRenderer>();
        if (!canvasRenderer)
            return;
        auto scene = g_pSceneManager->GetScene();
        scene->SetCanvasRenderer(canvasRenderer);
        Renderer::Start();
    }

    void CanvasRenderer::Render(ViewInfos viewInfos)
    {
        auto viewMat = camera->GetParent()->getComponent<Transform>()->getMatrix();
        auto projectMat = camera->getProjectionMatrixOrthographic();

        for (auto widgetPtr = m_Widgets.begin(); widgetPtr != m_Widgets.end(); widgetPtr++)
        {
            auto widget = *widgetPtr;

            SharedGameObject parent = widget->GetParent();
            auto modelMat = parent->getComponent<Transform>()->getMatrix();
            SharedMesh mesh = AssetManager::GetUIMesh();
            SharedMaterial material = AssetManager::LoadMaterial("Materials/defaultUI.gemtl");
            SharedMaterial m = make_shared<Material>();
            m->shaderID = material->shaderID;
            m->AddPropertys(material->m_MaterialDatas);
            m->AddProperty(glm::value_ptr(projectMat), "projection", 16 * sizeof(float), MaterialType::T_Mat4);
            m->AddProperty(glm::value_ptr(viewMat), "view", 16 * sizeof(float), MaterialType::T_Mat4);
            m->AddProperty(glm::value_ptr(modelMat), "model", 16 * sizeof(float), MaterialType::T_Mat4);

            RendererCammand rC;
            rC.material = material;
            rC.mesh = mesh;
            rC.index = 0;

            g_pGraphicsManager->addRendererCommand(rC);
        }
    }
}  // namespace GameEngine