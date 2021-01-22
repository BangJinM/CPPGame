#include <iostream>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GraphicsManager.h"
#include "glad/glad.h"
#include "Scene.h"
#include <GLFW/glfw3.h>
#include "SceneManager.h"
#include "AssetManager.h"
#include "ParserManager.h"
#include "ShaderManager.h"
#include <algorithm>

#include "Shader.h"
#include "Material.h"
#include "Mesh.h"

#include "imgui.h"

#include <string>
using namespace std;

GameEngineBegin extern AssetManager *g_pAssetManager;
extern GameEngineParser::ParserManager *g_pParserManager;
extern ShaderManager *g_pShaderManager;

int GraphicsManager::Initialize()
{
	int result;
	result = gladLoadGL();
	if (!result)
	{
		cerr << "OpenGL load failed!" << endl;
		result = -1;
	}
	else
	{
		result = 0;
		cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor << " loaded" << endl;

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		result = 0;
	}

	return result;
}

void GraphicsManager::Finalize()
{
}

void GraphicsManager::Tick()
{
	auto window = glfwGetCurrentContext();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	BaseGraphicsManager::Tick();
	m_RendererCommands.clear();
	glfwSwapBuffers(window);
}

void GraphicsManager::Clear()
{
}
void GraphicsManager::Draw()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	static bool show_another_window , show_demo_window = true;
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}

	// Rendering
	ImGui::Render();

	for (auto renderer = m_RendererCommands.begin(); renderer != m_RendererCommands.end(); renderer++)
	{
		PrepareMaterial(renderer->material);
		PrepareMesh(renderer->mesh, renderer->index);
	}
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GraphicsManager::PrepareMaterial(Material &material)
{
	int textureID = 0;
	auto shader = g_pShaderManager->GetShaderProgram(material.shaderID);
	shader->Use();
	for (size_t i = 0; i < material.m_MaterialDatas.size(); i++)
	{
		auto data = material.m_MaterialDatas[i];

		switch (data.m_Type)
		{
		case MaterialType::T_Mat4:
		{
			auto property = (float *)data.m_Buffer;
			shader->setMat4(data.m_Name, &property[0]);
			break;
		}
		case MaterialType::T_Texture:
		{
			auto property = (char *)data.m_Buffer;
			int location;
			location = glGetUniformLocation(shader->m_ProgramID, data.m_Name.c_str());
			if (location != -1)
			{
				SharedTexture image = g_pAssetManager->LoadTexture(property);
				if (!image)
					image = g_pAssetManager->getWhiteTexture();
				shader->setInt(data.m_Name, textureID);
				if (image->id <= 0)
				{
					BindTexture(image);
				}
				glActiveTexture(GL_TEXTURE0 + textureID);
				glBindTexture(GL_TEXTURE_2D, image->id);
				textureID++;
			}
			break;
		}
		default:
			break;
		}
	}
}

void GraphicsManager::BindTexture(SharedTexture texture)
{
	GLenum format;
	if (texture->formate == 1)
		format = GL_RED;
	else if (texture->formate == 3)
		format = GL_RGB;
	else if (texture->formate == 4)
		format = GL_RGBA;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, texture->Width, texture->Height, 0, format, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture->id = textureID;
}

void GraphicsManager::PrepareMesh(SharedMesh mesh, int index)
{
	if (mesh->isPrepare)
	{
		glBindVertexArray(mesh->m_MeshDatas[index].VAO);
		glDrawElements(GL_TRIANGLES, mesh->m_MeshDatas[index].indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		return;
	}
	for (size_t iMesh = 0; iMesh < mesh->m_MeshDatas.size(); iMesh++)
	{
		glGenVertexArrays(1, &mesh->m_MeshDatas[iMesh].VAO);
		glGenBuffers(1, &mesh->m_MeshDatas[iMesh].VBO);
		glGenBuffers(1, &mesh->m_MeshDatas[iMesh].EBO);

		glBindVertexArray(mesh->m_MeshDatas[iMesh].VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, mesh->m_MeshDatas[iMesh].VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, mesh->m_MeshDatas[iMesh].vertex.size() * sizeof(float), &mesh->m_MeshDatas[iMesh].vertex[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_MeshDatas[iMesh].EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->m_MeshDatas[iMesh].indices.size() * sizeof(unsigned int), &mesh->m_MeshDatas[iMesh].indices[0], GL_STATIC_DRAW);
		int offest = 0;
		for (size_t i = 0; i < mesh->m_MeshDatas[iMesh].attribs.size(); i++)
		{
			auto data = mesh->m_MeshDatas[iMesh].attribs[i];
			glEnableVertexAttribArray(data.vertexAttrib);
			glVertexAttribPointer(data.vertexAttrib, data.size, GL_FLOAT, GL_FALSE, mesh->m_MeshDatas[iMesh].vertexSizeInFloat * sizeof(float), (void *)offest);
			offest += data.attribSizeBytes;
		}
		glBindVertexArray(0);
	}
	mesh->isPrepare = true;
	PrepareMesh(mesh, index);
}

GameEngineEnd