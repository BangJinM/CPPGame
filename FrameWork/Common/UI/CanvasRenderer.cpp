#include "CanvasRenderer.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Material.h"
#include "Mesh.h"
#include "Widget.h"

namespace GameEngine
{
	CanvasRenderer::CanvasRenderer()
	{
		m_Mesh = std::make_shared<Mesh>();
	}

	CanvasRenderer::~CanvasRenderer()
	{
	}

	void CanvasRenderer::addWidget(std::shared_ptr<Widget> widget)
	{
		m_Widgets.push_back(widget);
		auto material = widget->GetMaterial();
		auto meshData = widget->GetMeshData();
		m_Materials.push_back(material);
		m_Mesh->m_MeshDatas.push_back(meshData);
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
} // namespace GameEngine