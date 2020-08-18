#include "Camera.h"
#include "GameObject.h"
#include "GraphicsManager.h"
#include "OpenGLDebugger.h"
#include "Mesh.h"
#include "MeshRenderer.h"
namespace GameEngine
{
	Camera::Camera(glm::float32 near, glm::float32 far, glm::float32 width, glm::float32 height, glm::float32 fieldofView)
		: m_Near(near), m_Far(far), m_ScreenWidth(width), m_ScreenHeight(height), m_FieldofView(fieldofView), Component(ClassID(Camera))
	{
		m_ProjectionMatrix4 = glm::perspective(glm::radians(m_FieldofView), m_ScreenWidth / m_ScreenHeight, this->m_Near, this->m_Far);
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		return this->m_ProjectionMatrix4;
	}

	void Camera::Render(std::list<std::shared_ptr<Renderer>> renderers)
	{
		auto viewMat = getParent()->getComponent<Transform>()->getMatrix();
		auto projectMat = m_ProjectionMatrix4;
		for (auto i = renderers.begin(); i != renderers.end(); i++)
		{
			auto renderer = std::dynamic_pointer_cast<MeshRenderer>(*i);
			std::shared_ptr<GameObject> parent = renderer->getParent();
			auto modelMat = parent->getComponent<Transform>()->getMatrix();
			std::shared_ptr<Mesh> mesh = renderer->getMesh();
			auto materials = renderer->getMaterials();
			for (size_t mi = 0; mi < mesh->m_MeshDatas.size(); mi++)
			{
				int materialID = 0;
				if (materials[materialID]){
					if (mi < materials.size())
						materialID = mi;
					auto material = Material::createMaterial(materials[materialID]);
					material->AddProperty(glm::value_ptr(projectMat), "projection", 16 * sizeof(float), MaterialType::Mat4);
					material->AddProperty(glm::value_ptr(viewMat), "view", 16 * sizeof(float), MaterialType::Mat4);
					material->AddProperty(glm::value_ptr(modelMat), "model", 16 * sizeof(float), MaterialType::Mat4);
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
	}

} // namespace GameEngine