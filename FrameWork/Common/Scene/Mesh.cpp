#include "Mesh.h"
#include <iostream>
namespace GameEngine
{
	GLenum glCheckError_(const char *file, int line)
	{
		GLenum errorCode;
		while ((errorCode = glGetError()) != GL_NO_ERROR)
		{
			std::string error;
			switch (errorCode)
			{
			case GL_INVALID_ENUM:
				error = "INVALID_ENUM";
				break;
			case GL_INVALID_VALUE:
				error = "INVALID_VALUE";
				break;
			case GL_INVALID_OPERATION:
				error = "INVALID_OPERATION";
				break;
			case GL_STACK_OVERFLOW:
				error = "STACK_OVERFLOW";
				break;
			case GL_STACK_UNDERFLOW:
				error = "STACK_UNDERFLOW";
				break;
			case GL_OUT_OF_MEMORY:
				error = "OUT_OF_MEMORY";
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				error = "INVALID_FRAMEBUFFER_OPERATION";
				break;
			}
			std::cout << error.c_str() << " | " << file << " (" << line << ")" << std::endl;
		}
		return errorCode;
	}
#define glCheckError() glCheckError_(__FILE__, __LINE__)
	Mesh::Mesh(MeshData *meshData, int material = -1)
	{
		m_MeshData = meshData;
		m_Material = material;
		setupMesh();
	}
	void Mesh::Draw()
	{
		// draw mesh
		if (m_Material)
		{
			//m_Material->use();
		}
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, m_MeshData->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glCheckError();
	}
	void Mesh::setupMesh()
	{
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, m_MeshData->vertex.size() * sizeof(float), &m_MeshData->vertex[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_MeshData->indices.size() * sizeof(unsigned int), &m_MeshData->indices[0], GL_STATIC_DRAW);
		glCheckError();
		int offest = 0;
		for (size_t i = 0; i < m_MeshData->attribs.size(); i++)
		{
			auto data = m_MeshData->attribs[i];
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, data.size, GL_FLOAT, GL_FALSE, m_MeshData->vertexSizeInFloat * sizeof(float), (void *)offest);
			offest += data.attribSizeBytes;
			glCheckError();
		}
		glCheckError();
		glBindVertexArray(0);
	}
} // namespace GameEngine