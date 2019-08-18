#ifndef SRC_RENDERERE_MESH_H__
#define SRC_RENDERERE_MESH_H__

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Shader.h"
#include "Material.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
};

class Mesh {
public:
	/*  ��������  */
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;
	/*  ����  */
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(Shader shader);

private:
	Material* m_Material;

	/*  ��Ⱦ����  */
	unsigned int VAO, VBO, EBO;

	/*  ����  */
	void setupMesh();
};

#endif
