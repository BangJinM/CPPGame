#include "GraphicsManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

#include "AssetManager.h"
#include "Camera.h"
#include "Material.h"
#include "Mesh.h"
#include "ParserManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "easylogging++.h"
#include "glm/glm.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
using namespace std;

namespace GameEngine
{
    extern AssetManager *g_pAssetManager;
    extern ParserManager *g_pParserManager;
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

            glEnable(GL_DEPTH_TEST);
            result = 0;
        }
        result = BaseGraphicsManager::Initialize();
        return result;
    }

    void GraphicsManager::Finalize()
    {
    }

    void GraphicsManager::Tick(float deltaTime)
    {
        auto window = glfwGetCurrentContext();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        BaseGraphicsManager::Tick(deltaTime);
        glfwSwapBuffers(window);
    }

    void GraphicsManager::Clear()
    {
    }

    void GraphicsManager::PrepareMaterial(RendererCammand rC)
    {
        auto material = rC.material;
        int textureID = 0;
        auto shader = g_pShaderManager->GetShaderProgram(material->shaderID);
        shader->Use();

        int location = glGetUniformLocation(shader->m_ProgramID, "model");
        if (location >= 0)
        {
            shader->setMat4("model", glm::value_ptr(rC.modelInfos.modelPos));
        }

        location = glGetUniformLocation(shader->m_ProgramID, "view");
        if (location >= 0)
        {
            shader->setMat4("view", glm::value_ptr(rC.viewInfos.view));
        }

        location = glGetUniformLocation(shader->m_ProgramID, "projection");
        if (location >= 0)
        {
            shader->setMat4("projection", glm::value_ptr(rC.viewInfos.project));
        }

        location = glGetUniformLocation(shader->m_ProgramID, "cameraPos");
        if (location >= 0)
        {
            shader->setVec3("cameraPos", rC.viewInfos.cameraPos);
        }

        // 	"Ambient":[0.1, 0.1, 0.1],
        // "Diffuse":[0.8, 0.8, 0.8],
        // "Specular":[1.0, 1.0, 1.0],
        // "color":[255, 255, 255, 255]
        location = glGetUniformLocation(shader->m_ProgramID, "light.direction");
        if (location >= 0)
        {
            shader->setVec3("light.direction", VecterFloat3(-0.2f, -1.0f, -0.3f));
        }

        location = glGetUniformLocation(shader->m_ProgramID, "light.ambient");
        if (location >= 0)
        {
            shader->setVec3("light.ambient", VecterFloat3(0.11, 0.1, 0.1));
        }

        location = glGetUniformLocation(shader->m_ProgramID, "light.diffuse");
        if (location >= 0)
        {
            shader->setVec3("light.diffuse", VecterFloat3(0.8, 0.8, 0.8));
        }

        location = glGetUniformLocation(shader->m_ProgramID, "light.specular");
        if (location >= 0)
        {
            shader->setVec3("light.specular", VecterFloat3(1.0, 1.0, 1.0));
        }

        for (size_t i = 0; i < material->m_MaterialDatas.size(); i++)
        {
            switch (material->m_MaterialDatas[i].m_Type)
            {
            case MaterialType::T_Mat4:
            {
                auto property = reinterpret_cast<float *>(material->m_MaterialDatas[i].m_Buffer->GetData());
                shader->setMat4(material->m_MaterialDatas[i].m_Name, &property[0]);
                break;
            }
            case MaterialType::T_Texture:
            {
                string property = reinterpret_cast<char *>(material->m_MaterialDatas[i].m_Buffer->GetData());
                int location = glGetUniformLocation(shader->m_ProgramID, material->m_MaterialDatas[i].m_Name.c_str());
                if (location != -1)
                {
                    SharedTexture image = g_pAssetManager->LoadTexture(property);
                    if (!image)
                        image = g_pAssetManager->getWhiteTexture();
                    shader->setInt(material->m_MaterialDatas[i].m_Name, textureID);
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

    void GraphicsManager::BindCubeTexture(SharedCube cube)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        for (unsigned int i = 0; i < 6; i++)
        {
            auto cubeValue = cube->GetValueByDir(i);
            SharedTexture image = g_pAssetManager->LoadTexture(cubeValue.path);
            if (!image)
                image = g_pAssetManager->getWhiteTexture();
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, image->Width, image->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data);
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        cube->SetTextureID(textureID);
    }

    void GraphicsManager::DrawCubeTexture(SharedCube cube, int shaderID)
    {
        if (!cube)
            return;

        auto shader = g_pShaderManager->GetShaderProgram(shaderID);
        glDepthFunc(GL_LEQUAL);
        shader->Use();

        auto scene = g_pSceneManager->GetScene();
        SharePtr<Camera> camera = *(scene->m_Cameras.begin());
        auto cameraTs = camera->getParent()->getComponent<Transform>();

        auto view = glm::mat4(glm::mat3(cameraTs->getMatrix())); 
        shader->setMat4("view", cameraTs->getMatrix());

        shader->setMat4("projection", camera->getProjectionMatrix());

        shader->setInt("skybox", 0);
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_CUBE_MAP, cube->GetTextureID());

        PrepareMesh(cube->GetMesh(), 0);
        glDepthFunc(GL_LESS);
    }

    void GraphicsManager::PrepareMesh(SharedMesh mesh, int index)
    {
        if (!mesh)
            return;
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

}  // namespace GameEngine