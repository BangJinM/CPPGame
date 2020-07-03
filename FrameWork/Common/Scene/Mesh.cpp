#include "Mesh.h"
#include "OpenGLDebugger.h"
namespace GameEngine
{
	
	Mesh::Mesh(MeshData *meshData)
	{
		m_MeshData = meshData;
		setupMesh();
	}
	void Mesh::Draw()
	{
		// draw mesh
		//OpenGLDebugger::glCheckError();
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, m_MeshData->indices.size(), GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);
		//OpenGLDebugger::glCheckError();
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
		OpenGLDebugger::glCheckError();
		int offest = 0;
		for (size_t i = 0; i < m_MeshData->attribs.size(); i++)
		{
			auto data = m_MeshData->attribs[i];
			glEnableVertexAttribArray(data.vertexAttrib);
			glVertexAttribPointer(data.vertexAttrib, data.size, GL_FLOAT, GL_FALSE, m_MeshData->vertexSizeInFloat * sizeof(float), (void *)offest);
			offest += data.attribSizeBytes;
			OpenGLDebugger::glCheckError();
		}
		OpenGLDebugger::glCheckError();
		glBindVertexArray(0);
	}
} // namespace GameEngine