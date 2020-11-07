#include "CanvasRenderer.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Material.h"
#include "Mesh.h"
#include "Widget.h"
#include "Transform.h"
#include "Camera.h"

#include "BaseGraphicsManager.h"

GameEngineBegin

extern BaseGraphicsManager *g_pGraphicsManager;

CanvasRenderer::CanvasRenderer()
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
	auto canvasRenderer = getParent()->getComponent<CanvasRenderer>();
	if (!canvasRenderer)
		return;
	auto scene = SceneManager::GetInstance()->GetScene();
	scene->SetCanvasRenderer(canvasRenderer);
	Renderer::Start();
}

void CanvasRenderer::Render(SharePtr<Camera> camera)
{
	auto viewMat = camera->getParent()->getComponent<Transform>()->getMatrix();
	auto projectMat = camera->getProjectionMatrixOrthographic();

	for (auto widgetPtr = m_Widgets.begin(); widgetPtr != m_Widgets.end(); widgetPtr++)
	{
		auto widget = *widgetPtr;

		SharedGameObject parent = widget->getParent();
		auto modelMat = parent->getComponent<Transform>()->getMatrix();
		MeshData meshData = widget->GetMeshData();
		auto materials = widget->GetMaterial();

		
		Material material = *materials;
		material.AddProperty(glm::value_ptr(projectMat), "projection", 16 * sizeof(float), MaterialType::T_Mat4);
		material.AddProperty(glm::value_ptr(viewMat), "view", 16 * sizeof(float), MaterialType::T_Mat4);
		material.AddProperty(glm::value_ptr(modelMat), "model", 16 * sizeof(float), MaterialType::T_Mat4);

		RendererCammand rC;
		rC.material = material;
		rC.meshData = meshData;

		g_pGraphicsManager->addRendererCommand(rC);
	}
}
GameEngineEnd