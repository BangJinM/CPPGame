#ifndef SRC_RENDERERE_MESH_H__
#define SRC_RENDERERE_MESH_H__

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Renderer/Shader.h"
#include "Renderer/Material.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::vec2 texCoords;
};

struct MeshTexture
{
	unsigned int id;
	std::string type;
	std::string path;
	Texture2D* texture;
};

class Mesh {
public:
	/*  网格数据  */
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<MeshTexture> m_Textures;
	/*  函数  */
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures);

	void Draw(Shader shader);

private:
	Material* m_Material;

	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;

	/*  函数  */
	void setupMesh();
};

#endif
