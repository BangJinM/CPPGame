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

	void CanvasRenderer::Render(std::shared_ptr<Camera> camera)
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