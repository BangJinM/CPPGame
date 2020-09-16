#include "CanvasRenderer.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Material.h"
#include "Mesh.h"
#include "Widget.h"
#include "Transform.h"
#include "Camera.h"

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

	void CanvasRenderer::Render(std::shared_ptr<Camera> camera)
	{
		auto viewMat = camera->getParent()->getComponent<Transform>()->getMatrix();
		auto projectMat = camera->getProjectionMatrix();

		for (auto widgetPtr = m_Widgets.begin(); widgetPtr != m_Widgets.end(); widgetPtr++)
		{
			auto widget = *widgetPtr;

			std::shared_ptr<GameObject> parent = widget->getParent();
			auto modelMat = parent->getComponent<Transform>()->getMatrix();
			MeshData meshData = widget->GetMeshData();
			auto materials = widget->GetMaterial();

			auto material = Material::createMaterial(materials);
			auto matArray = glm::value_ptr(modelMat);
			float initArray[4][4];
			for (size_t i = 0; i < 4; i++)
			{
				for (size_t j = 0; j < 4; j++)
				{
					initArray[i][j] = matArray[i * 4 + j];
				}
			}

			material->AddProperty(glm::value_ptr(projectMat), "projection", 16 * sizeof(float), MaterialType::T_Mat4);
			material->AddProperty(glm::value_ptr(viewMat), "view", 16 * sizeof(float), MaterialType::T_Mat4);
			material->AddProperty(glm::value_ptr(modelMat), "model", 16 * sizeof(float), MaterialType::T_Mat4);
			material->Prepare();

			auto meshdata = meshData;
			glBindVertexArray(meshdata.VAO);
			glDrawElements(GL_TRIANGLES, meshdata.indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
			
		}
	}
} // namespace GameEngine