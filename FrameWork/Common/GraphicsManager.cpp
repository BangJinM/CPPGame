#include <iostream>
#include "GraphicsManager.h"
#include "AssetLoader.h"
#include "glad/glad.h"

#include "Scene.h"

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
            }

            m_Scene = new Scene();

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
        m_Scene->Draw();
    }

    void GraphicsManager::Clear()
    {
    }
} // namespace GameEngine