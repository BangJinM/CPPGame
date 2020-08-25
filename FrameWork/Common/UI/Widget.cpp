#include "Widget.h"
#include "MyMath.h"
#include "Shader.h"
namespace GameEngine
{
	Widget::Widget() : Component(ClassID(Undefined))
	{
	}

	Widget::~Widget()
	{
	}

	void Widget::InitComponent(std::shared_ptr<GameObject> host)
	{
		Component::InitComponent(host);
	}

	void Widget::setCanvasRenderer(std::shared_ptr<CanvasRenderer> canvasRenderer)
	{
	}

	MeshData& Widget::getDefaultData()
	{
		MeshData meshData;
		meshData.indices = {
			0, 1, 3, // first triangle
			1, 2, 3	 // second triangle
		};

		MeshVertexAttrib attrib;
		attrib.size = 3;
		attrib.type = GL_FLOAT;

		attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_POSITION;
		attrib.attribSizeBytes = attrib.size * sizeof(float);
		meshData.attribs.push_back(attrib);
		meshData.vertexSizeInFloat += 3;

		attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_COLOR;
		attrib.attribSizeBytes = attrib.size * sizeof(float);
		meshData.attribs.push_back(attrib);
		meshData.vertexSizeInFloat += 3;

		attrib.size = 2;
		attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_TEX_COORD;
		attrib.attribSizeBytes = attrib.size * sizeof(float);
		meshData.attribs.push_back(attrib);
		meshData.vertexSizeInFloat += 2;

		std::vector<float> vertices;
		for (size_t i = 0; i < 4; i++)
		{
			meshData.vertex.push_back(position[i][0]);
			meshData.vertex.push_back(position[i][1]);
			meshData.vertex.push_back(position[i][2]);

			meshData.vertex.push_back(color[i][0]);
			meshData.vertex.push_back(color[i][1]);
			meshData.vertex.push_back(color[i][2]);

			meshData.vertex.push_back(textcoord[i][0]);
			meshData.vertex.push_back(textcoord[i][1]);
		}
		meshData.setupMesh();
		return meshData;
	}

	void Widget::setDefaultData()
	{
		position[0] = vecterFloat3(0.5f, 0.5f, 0.0f);
		position[1] = vecterFloat3(0.5f, -0.5f, 0.0f);
		position[2] = vecterFloat3(-0.5f, -0.5f, 0.0f);
		position[3] = vecterFloat3(-0.5f, 0.5f, 0.0f);

		color[0] = vecterFloat3(1.0f, 0.0f, 0.0f);
		color[1] = vecterFloat3(0.0f, 1.0f, 0.0f);
		color[2] = vecterFloat3(0.0f, 0.0f, 1.0f);
		color[3] = vecterFloat3(1.0f, 1.0f, 0.0f);

		textcoord[0] = vecterFloat2(1.0f, 1.0f);
		textcoord[1] = vecterFloat2(1.0f, 0.0f);
		textcoord[2] = vecterFloat2(0.0f, 0.0f);
		textcoord[3] = vecterFloat2(0.0f, 1.0f);
	}

	void Widget::setDefaultMesh()
	{
		setDefaultData();
		m_MeshData = getDefaultData();
	}
} // namespace GameEngine