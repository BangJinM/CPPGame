#include "Mesh.h"
#include "OpenGLDebugger.h"
namespace GameEngine
{

	void MeshData::setupMesh()
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
		glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), &vertex[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		OpenGLDebugger::glCheckError();
		int offest = 0;
		for (size_t i = 0; i < attribs.size(); i++)
		{
			auto data = attribs[i];
			glEnableVertexAttribArray(data.vertexAttrib);
			glVertexAttribPointer(data.vertexAttrib, data.size, GL_FLOAT, GL_FALSE, vertexSizeInFloat * sizeof(float), (void *)offest);
			offest += data.attribSizeBytes;
			OpenGLDebugger::glCheckError();
		}
		OpenGLDebugger::glCheckError();
		glBindVertexArray(0);
	}
} // namespace GameEngine