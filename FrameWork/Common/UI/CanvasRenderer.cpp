#include "CanvasRenderer.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
namespace GameEngine
{
	CanvasRenderer::CanvasRenderer()
	{
	}

	CanvasRenderer::~CanvasRenderer()
	{
	}

	void CanvasRenderer::addWidget(std::shared_ptr<Widget> widget)
	{
	}

	void CanvasRenderer::getWidget()
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
		Component::Start();
	}
} // namespace GameEngine