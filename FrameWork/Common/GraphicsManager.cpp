#include <iostream>
#include "GraphicsManager.h"
#include "AssetLoader.h"
#include "glad/glad.h"
//一下测试
#include "ObjParser.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Camera.h"
#include "GameObject.h"
#include "Shader.h"
#include "ObjMaterialParser.h"

using namespace std;

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;

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

            if (GLAD_GL_VERSION_3_0)
            {
                // Set the depth buffer to be entirely cleared to 1.0 values.
                glClearDepth(1.0f);

                // Enable depth testing.
                glEnable(GL_DEPTH_TEST);

                // Set the polygon winding to front facing for the right handed system.
                glFrontFace(GL_CW);

                // Enable back face culling.
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);

                // Initialize the world/model matrix to the identity matrix.
                // BuildIdentityMatrix(m_worldMatrix);

                // // Set the field of view and screen aspect ratio.
                // float fieldOfView = PI / 4.0f;
                // const GfxConfiguration &conf = g_pApp->GetConfiguration();

                // float screenAspect = (float)conf.screenWidth / (float)conf.screenHeight;

                // Build the perspective projection matrix.
                // BuildPerspectiveFovLHMatrix(m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

                // 摄像机
                Camera *camera = new Camera();
                cameraObject = new GameObject();
                cameraObject->addComponent(camera);
                std::string vert = g_pAssetLoader->SyncOpenAndReadTextFileToString("Shaders/default.vert");
                std::string flag = g_pAssetLoader->SyncOpenAndReadTextFileToString("Shaders/default.flag");
                //Shader shader(vert, flag);

                //Material material = Material(&shader);

                std::vector<tinyobj::shape_t> shapes;
                std::vector<tinyobj::material_t> materials;
                tinyobj::LoadObj(shapes, materials, "Scene/model.obj", "Materials/");
                ObjParser parser;
                gameobject = parser.Parse(shapes);
                ObjMaterialParser omp;
                omp.Parse(materials);
            }

            // InitializeShader(VS_SHADER_SOURCE_FILE, PS_SHADER_SOURCE_FILE);
            // InitializeBuffers();
            result = 1;
        }

        return result;
    }

    void GraphicsManager::Finalize()
    {
    }

    void GraphicsManager::Tick()
    {
        //
    }

    void GraphicsManager::Draw()
    {
        gameobject->draw();
    }

    void GraphicsManager::Clear()
    {
    }
} // namespace GameEngine