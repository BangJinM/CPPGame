#include "OpenGLWidget.h"

#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShader>
#include <QOpenGLWidget>

#include "AssetManager.h"
#include "BaseGraphicsManager.h"
#include "MShader.h"
#include "Scene.h"
#include "SceneManager.h"

using namespace GameEngine;

namespace GameEngine
{
    extern BaseGraphicsManager *g_pGraphicsManager;
    extern AssetManager *g_pAssetManager;
    extern SceneManager *g_pSceneManager;
}  // namespace GameEngine

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
}

void OpenGLWidget::paintGL()
{
    glClearColor(0.3, 0.3, 0.3, 1);
    Tick();
}

void OpenGLWidget::initializeGL()
{
    Initialize();
    glClearColor(0.3, 0.3, 0.3, 1);
}

int OpenGLWidget::Initialize()
{
    initializeOpenGLFunctions();
    int result;
    SharePtr<Scene> m_Scene;
    m_Scene = std::make_shared<Scene>();
    m_Scene->LoadSceneByPath("Scene/defaultEx.scene");
    g_pSceneManager->SetNextScene(m_Scene);
    result = 1;
    return result;
}

void OpenGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLWidget::Finalize()
{
}

void OpenGLWidget::Tick()
{
    g_pGraphicsManager->Tick();
    auto m_RendererCommands = g_pGraphicsManager->getRendererCommand();
    Draw(m_RendererCommands);
    g_pGraphicsManager->Clear();
}

void OpenGLWidget::Clear()
{
}

void OpenGLWidget::Draw(std::list<RendererCammand> m_RendererCommands)
{
    for (auto renderer = m_RendererCommands.begin(); renderer != m_RendererCommands.end(); renderer++)
    {
        //        PrepareMaterial(renderer->material);
        PrepareMesh(renderer->mesh, renderer->index);
    }
}

void OpenGLWidget::PrepareMaterial(Material &material)
{
    int textureID = 0;
    bool flag = material.shader->Use();
    for (size_t i = 0; i < material.m_MaterialDatas.size(); i++)
    {
        auto data = material.m_MaterialDatas[i];

        switch (data.m_Type)
        {
        case MaterialType::T_Mat4:
        {
            auto property = (float *)data.m_Buffer;
            material.shader->setMat4(data.m_Name, &property[0]);
            break;
        }
        case MaterialType::T_Texture:
        {
            auto property = (char *)data.m_Buffer;
            unsigned int location;
            location = material.shader->uniformLocation(data.m_Name.c_str());
            if (location != -1)
            {
                SharedTexture image = g_pAssetManager->LoadTexture(property);
                if (!image)
                    image = g_pAssetManager->getWhiteTexture();
                material.shader->setInt(data.m_Name, textureID);
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

void OpenGLWidget::BindTexture(SharedTexture texture)
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

void OpenGLWidget::PrepareMesh(SharedMesh mesh, int index)
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
