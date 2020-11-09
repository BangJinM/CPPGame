﻿#include <iostream>
#include "GraphicsManager.h"
#include "glad/glad.h"
#include "Scene.h"
#include <GLFW/glfw3.h>
#include "SceneManager.h"
#include "AssetManager.h"

#include "Material.h"
#include "Mesh.h"

#include "Shader.h"

using namespace std;

GameEngineBegin

extern AssetManager *g_pAssetManager;

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

        SharePtr<Scene> m_Scene;
        m_Scene = std::make_shared<Scene>();
        m_Scene->LoadSceneByPath("Scene/defaultEx.scene");
        SceneManager::GetInstance()->SetNextScene(m_Scene);
        result = 1;
    }

    return result;
}

void GraphicsManager::Finalize()
{
}

void GraphicsManager::Tick()
{
    auto window = glfwGetCurrentContext();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_RendererCommands.clear();
    BaseGraphicsManager::Tick();
    glfwSwapBuffers(window);
}

void GraphicsManager::Clear()
{
}


void GraphicsManager::Draw()
{
	for each (auto renderer in m_RendererCommands)
	{
		PrepareMaterial(renderer.material);
		PrepareMesh(renderer.mesh,renderer.index);
	}
}

void GraphicsManager::PrepareMaterial(Material& material){ 
	Shader shader( material.vert.value, material.vert.path, material.frag.value, material.frag.path);
    int textureID = 0;
	shader.use();
	for (size_t i = 0; i < material.m_MaterialDatas.size(); i++)
	{
		auto data = material.m_MaterialDatas[i];

		switch (data.m_Type)
		{
		case MaterialType::T_Mat4:
		{
			auto property = (float *)data.m_Buffer;
			shader.setMat4(data.m_Name, &property[0]);
			break;
		}
		case MaterialType::T_Texture:
		{
			auto property = (char *)data.m_Buffer;
			unsigned int location;
			location = glGetUniformLocation(shader.ID, data.m_Name.c_str());
			if (location != -1)
			{
				SharedTexture image = g_pAssetManager->LoadTexture(property);
				if (!image)
					image = g_pAssetManager->getWhiteTexture();
				shader.setInt(data.m_Name, textureID);
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

void GraphicsManager::PrepareMesh(SharedMesh mesh,int index){
	if (mesh->isPrepare) {
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